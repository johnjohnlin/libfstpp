// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
// direct include
#include "fstcpp/fstcpp_writer.h"
// C system headers
// C++ standard library headers
#include <cstdint>
#include <iostream>
#include <numeric>
// Other libraries' .h files.
#include <gtest/gtest.h>
// Your project's .h files.

using namespace std;

static const string V2S(vector<uint8_t> &v) {
	return string(reinterpret_cast<char *>(v.data()), v.size());
}

namespace fst {

// This test focuses on testing the emit functions of Writer
// The name of this test is not unique
// but it is not a problem since Writer_*.test.cpp are individual
// binary files
class WriterTest : public ::testing::Test {
protected:
	static void writeHeader(const Header &h, ostream &os) { Writer::writeHeader_(h, os); }

	// For testing internal function called by flushValueChangeData.
	// We need to verify the internal function behavior
	// since value change data is too complex to test as a whole.
	static void flushValueChangeData_Timestamps(
		vector<uint8_t> &buf, const vector<uint64_t> &timestamps
	) {
		detail::ValueChangeData vcd;
		vcd.timestamps = timestamps;
		vcd.writeTimestamps(buf);
	}

	static vector<int64_t> flushValueChangeData_ValueChanges_UniquifyWaveData(
		vector<vector<uint8_t>> &data
	) {
		return detail::ValueChangeData::uniquifyWaveData(data);
	}

	static uint64_t flushValueChangeData_ValueChanges_EncodePositionsAndwriteUniqueWaveData(
		ostringstream &os, const vector<vector<uint8_t>> &data, vector<int64_t> &positions
	) {
		return detail::ValueChangeData::encodePositionsAndwriteUniqueWaveData(
			os, data, positions, WriterPackType::NO_COMPRESSION
		);
	}

	static void flushValueChangeData_EncodedPositions(
		ostringstream &os, const vector<int64_t> &encoded_positions
	) {
		detail::ValueChangeData::writeEncodedPositions(encoded_positions, os);
	}
};

////////////////////////////////////////////////
// Tests for flushValueChangeData_ValueChanges_UniquifyWaveData
////////////////////////////////////////////////
TEST_F(WriterTest, flushValueChangeData_ValueChanges_UniquifyWaveData_NoData) {
	vector<vector<uint8_t>> data;
	auto positions = flushValueChangeData_ValueChanges_UniquifyWaveData(data);
	EXPECT_TRUE(positions.empty());
}

TEST_F(WriterTest, flushValueChangeData_ValueChanges_UniquifyWaveData_AllEmpty) {
	vector<vector<uint8_t>> data = {{}, {}, {}};
	auto positions = flushValueChangeData_ValueChanges_UniquifyWaveData(data);
	EXPECT_EQ(positions.size(), 3);
	EXPECT_EQ(positions[0], 0);
	EXPECT_EQ(positions[1], 0);
	EXPECT_EQ(positions[2], 0);
}

TEST_F(WriterTest, flushValueChangeData_ValueChanges_UniquifyWaveData_NoDuplicates) {
	vector<vector<uint8_t>> data = {{'a', 'b'}, {'c', 'd'}, {'e', 'f'}};
	auto positions = flushValueChangeData_ValueChanges_UniquifyWaveData(data);
	EXPECT_EQ(positions.size(), 3);
	EXPECT_EQ(positions[0], 0);
	EXPECT_EQ(positions[1], 0);
	EXPECT_EQ(positions[2], 0);
	// Data should remain unchanged
	EXPECT_EQ(data[0], vector<uint8_t>({'a', 'b'}));
	EXPECT_EQ(data[1], vector<uint8_t>({'c', 'd'}));
	EXPECT_EQ(data[2], vector<uint8_t>({'e', 'f'}));
}

TEST_F(WriterTest, flushValueChangeData_ValueChanges_UniquifyWaveData_WithDuplicates) {
	vector<vector<uint8_t>> data = {
		{'a', 'b'},
		{'c', 'd'},
		{'a', 'b'},  // duplicate of [0]
		{'e', 'f'},
		{'a', 'b'},  // duplicate of [0]
		{'e', 'f'}   // duplicate of [3]
	};
	auto positions = flushValueChangeData_ValueChanges_UniquifyWaveData(data);
	EXPECT_EQ(positions.size(), 6);
	EXPECT_EQ(positions[0], 0);
	EXPECT_EQ(positions[1], 0);
	EXPECT_EQ(positions[2], -1);  // duplicate, encoded as -(0 + 1)
	EXPECT_EQ(positions[3], 0);
	EXPECT_EQ(positions[4], -1);  // duplicate, encoded as -(0 + 1)
	EXPECT_EQ(positions[5], -4);  // duplicate, encoded as -(3 + 1)
	// Duplicated data should be cleared
	EXPECT_TRUE(data[2].empty());
	EXPECT_TRUE(data[4].empty());
	EXPECT_TRUE(data[5].empty());
	// Original data should remain intact
	EXPECT_EQ(data[0], vector<uint8_t>({'a', 'b'}));
	EXPECT_EQ(data[1], vector<uint8_t>({'c', 'd'}));
	EXPECT_EQ(data[3], vector<uint8_t>({'e', 'f'}));
}

////////////////////////////////////////////////
// Tests for flushValueChangeData_ValueChanges_EncodePositionsAndwriteUniqueWaveData
////////////////////////////////////////////////
TEST_F(
	WriterTest, flushValueChangeData_ValueChanges_EncodePositionsAndwriteUniqueWaveData_Negative
) {
	vector<vector<uint8_t>> data = {
		{},               // empty, positions[0] must be 0
		{'a', 'b'},       // the first block to write, positions[1] must be 0
		{},               // empty, positions[2] must be 0
		{'z'},            // positions[3] is negative, this data is ignored
		{'c', 'd', 'e'},  // the second block to write, positions[4] must be 0
	};
	vector<int64_t> positions = {
		// empty, positions[0] is unchanged
		0,
		// first non-empty block, positions[1] will be set to 1 after encoding
		0,
		// empty, positions[2] is unchanged
		0,
		// negative, positions[3] is unchanged
		-99,
		// second non-empty block, positions[4] will be set to
		// the size of previous block 3 (LEB128(0) + "ab")
		// after encoding
		0,
	};
	ostringstream os;
	uint64_t count = flushValueChangeData_ValueChanges_EncodePositionsAndwriteUniqueWaveData(
		os, data, positions
	);

	// Verify count: 2 non-empty blocks ('ab' and 'cde') passed through
	EXPECT_EQ(count, 2);

	EXPECT_EQ(positions[0], 0);
	EXPECT_EQ(positions[1], 1);
	EXPECT_EQ(positions[2], 0);
	EXPECT_EQ(positions[3], -99);
	EXPECT_EQ(positions[4], 3);

	// Output: LEB128(0) + "ab" + LEB128(0) + "cde"
	// 0 means no compression
	// TODO how to test if we implement compressed data?
	string expected =
		"\x00"
		"ab"
		"\x00"
		"cde"s;
	EXPECT_EQ(os.str(), expected);
}

////////////////////////////////////////////////
// Test for flushValueChangeData_EncodedPositions
////////////////////////////////////////////////
TEST_F(WriterTest, flushValueChangeData_EncodedPositions) {
	// Consolidated test with boundary values
	// 0, 1, -1, 127, -127, 128, -128
	vector<int64_t> positions = {0, 0, 0, 1, -1, 127, -127, 128, -128};
	ostringstream os;
	flushValueChangeData_EncodedPositions(os, positions);

	// 0    -> length 3 -> (1<<1)|0 = 6   -> [0x06]
	// 1    -> (1<<1)|1 = 3               -> [0x03]
	// -1   -> (-1<<1)|1 = -1             -> [0x7F]
	// 127  -> (127<<1)|1 = 255           -> [0xFF, 0x01]
	// -127 -> (-127<<1)|1 = -253         -> [0x83, 0x7E]
	// 128  -> (128<<1)|1 = 257           -> [0x81, 0x02]
	// -128 -> (-128<<1)|1 = -255         -> [0x81, 0x7E]

	string expected =
		"\x06"
		"\x03"
		"\x7F"
		"\xFF\x01"
		"\x83\x7E"
		"\x81\x02"
		"\x81\x7E"s;

	EXPECT_EQ(os.str(), expected);
}

TEST_F(WriterTest, flushValueChangeData_6BitsLengthZeros) {
	// Consolidated test with boundary values
	// 35 zeros
	vector<int64_t> positions(35, 0);
	ostringstream os;
	flushValueChangeData_EncodedPositions(os, positions);

	// 0 -> length 35 -> (35<<1)|0 = 70 -> [0x46]
	// This 0x46 (7-bit) shall be encoded as unsigned LEB128
	// Not signed LEB128 (which shall be 2 bytes)
	string expected = "\x46"s;

	EXPECT_EQ(os.str(), expected);
}

////////////////////////////////////////////////
// Tests for flushValueChangeData_Timestamps
////////////////////////////////////////////////
TEST_F(WriterTest, flushValueChangeData_Timestamps) {
	vector<uint64_t> timestamps;
	// generate [0, {7'b1}, {7'b1, 7'b2}] ... to 56-bits (Verilog notation)
	timestamps.reserve(9);
	timestamps.push_back(0);
	for (uint64_t i = 1, val = 0; i <= 8; ++i) {
		val |= i << ((i - 1) * 7);
		timestamps.push_back(val);
	}
	// cumsum first since the function encodes timestamps as deltas
	partial_sum(timestamps.begin(), timestamps.end(), timestamps.begin());

	vector<uint8_t> buf;
	flushValueChangeData_Timestamps(buf, timestamps);
	// Expected varint encoding of the timestamps
	// The LEB128 shall looks like 1 12 123 1234 with the 1 becomes 0x81
	string expected =
		"\x00"
		"\x01"
		"\x81\x02"
		"\x81\x82\x03"
		"\x81\x82\x83\x04"
		"\x81\x82\x83\x84\x05"
		"\x81\x82\x83\x84\x85\x06"
		"\x81\x82\x83\x84\x85\x86\x07"
		"\x81\x82\x83\x84\x85\x86\x87\x08"s;
	EXPECT_EQ(V2S(buf), expected);
}

}  // namespace fst
