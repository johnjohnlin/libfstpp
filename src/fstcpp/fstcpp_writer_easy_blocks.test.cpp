// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
// direct include
#include "fstcpp/fstcpp_writer.h"
// C system headers
// C++ standard library headers
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
// Other libraries' .h files.
#include <gtest/gtest.h>
// Your project's .h files.
#include "fstcpp/fstcpp_file.h"
#include "fstcpp/fstcpp_stream_write_helper.h"

using namespace std;

namespace fst {

// This test focus on testing the emit functions of Writer
// The name of this test is not unique
// but it is not a problem since Writer_*.test.cpp are individual
// binary files
class WriterTest : public ::testing::Test {
protected:
	// For testing set(Up)Scope/createVar
	// We call Writer API and get the buffer content
	// without inspecting the internal state of Writer
	static const string GetHierarchyBuffer(Writer &Writer) {
		return string(
			reinterpret_cast<char *>(Writer.hierarchy_buffer_.data()),
			Writer.hierarchy_buffer_.size()
		);
	}

	static const string GetGeometryBuffer(Writer &Writer) {
		return string(
			reinterpret_cast<char *>(Writer.geometry_buffer_.data()), Writer.geometry_buffer_.size()
		);
	}

	static void writeHeader(const Header &h, ostream &os) { Writer::writeHeader_(h, os); }

	static void appendBlackout(Writer &Writer, std::ostream &os) { Writer.appendBlackout_(os); }
};

TEST_F(WriterTest, createVar) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	// Call createVar
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_WIRE,
			fst::Hierarchy::VarDirection::INPUT,
			/*bitwidth =*/8,
			"valid",
			/*alias handle =*/0
		),
		1u
	);

	// Second Call createVar
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_PORT,
			fst::Hierarchy::VarDirection::OUTPUT,
			/*bitwidth =*/5566,
			"ready",
			/*alias handle =*/0
		),
		2u
	);

	// Get the hierarchy buffer content
	string buf = GetHierarchyBuffer(Writer);
	// expected: Type, Direction, Name, bitwidth, Alias Handle
	// FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
	string expected =
		"\x10\x01valid\x00\x08\x00"s
		"\x12\x02ready\x00\xbe\x2b\x00"s;
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, createVarAlias) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	// Call createVar
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_WIRE,
			fst::Hierarchy::VarDirection::INPUT,
			/*bitwidth =*/1,
			"clk",
			/*alias handle =*/0
		),
		1u
	);

	// Second Call createVar
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_PORT,
			fst::Hierarchy::VarDirection::OUTPUT,
			/*bitwidth =*/0xd,  // don't care
			"aliasclk",
			/*alias handle =*/1
		),
		1u
	);

	// Get the hierarchy buffer content
	string buf = GetHierarchyBuffer(Writer);
	// expected: Type, Direction, Name, bitwidth, Alias Handle
	// FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
	string expected =
		"\x10\x01"
		"clk\x00\x01\x00"s
		"\x12\x02"
		"aliasclk\x00\x0d\x01"s;
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, createAliasOutOfRange) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	// Call createVar
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_WIRE,
			fst::Hierarchy::VarDirection::INPUT,
			/*bitwidth =*/16,
			"mode",
			/*alias handle =*/0
		),
		1u
	);

	// Get the hierarchy buffer content
	string buf = GetHierarchyBuffer(Writer);
	// expected: Type, Direction, Name, bitwidth, Alias Handle
	// FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
	string expected = "\x10\x01mode\x00\x10\x00"s;
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, Scope) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	// set Scope
	Writer.setScope(
		fst::Hierarchy::ScopeType::VCD_MODULE,
		"top",
		"component"
	);  // TODO: what is this?
	Writer.upscope();

	// Get the hierarchy buffer content
	string buf = GetHierarchyBuffer(Writer);
	// expected: Scope Type, Name, component, Upscope
	string expected =
		"\xfe\x00top\x00"
		"component\x00"
		"\xff"s;
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, createEnumTable_NoEscape_Padding) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	// Call createEnumTable
	Writer.createEnumTable(
		"E1 Hello World",
		3,  // test padding
		{{"A", "0"}, {"B", "001"}, {"C", "1101"}}
	);
	// Get the hierarchy buffer content
	string buf = GetHierarchyBuffer(Writer);
	string expected = (
		// AttrBegin->Misc->EnumTable
		"\xfc\x00\x07"
		// enum name
		"E1 Hello World "
		// number of entries (in string!)
		"3 "
		// keys
		"A B C "
		// values; padding to at least 3 bytes
		"000 001 1101\x00"
		// LEB128 of 1
		"\x01"s
	);
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, createEnumTable_Escape_NoPadding) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	Writer.createEnumTable(
		"E2.hello.world",  // test escape
		0,                 // test no padding
		{
			{"\a", "000"},
			{"\b", "001"},
			{"\f", "010"},
			{"\n", "011"},
			{"\r", "100"},
			{"\t", "101"},
			{"\v", "110"},
			{"\\", "111"},
			{"?", "1000"},
			{"\'", "1001"},
			{"\"", "1010"},
			{"\321", "1011"},
		}
	);

	// Get the hierarchy buffer content
	string buf = GetHierarchyBuffer(Writer);
	string expected = (
		// AttrBegin->Misc->EnumTable
		"\xfc\x00\x07"
		// enum name; escaped
		"E2.hello.world "
		// number of entries (in string!)
		"12 "
		// keys
		R"(\a \b \f \n \r \t \v \\ \? \' \" \321 )"
		// values; no padding
		"000 001 010 011 100 101 110 111 1000 1001 1010 1011\x00"
		// LEB128 of 1
		"\x01"s
	);
	EXPECT_EQ(buf.size(), expected.size());
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, createEnumTableRef) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	Writer.emitEnumTableRef((0x12 << 7) | 0x34);
	string buf = GetHierarchyBuffer(Writer);
	string expected = (
		// AttrBegin->Misc->EnumTableRef
		"\xFC\x00\x07"
		// null terminated empty string
		"\0"
		// LEB128 of 0x12<<7 | 0x34
		"\xB4\x12"s
	);
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, createVarVcdReal) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	// Call createVar with eVcdReal
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_REAL,
			fst::Hierarchy::VarDirection::INPUT,
			/*bitwidth =*/0,  // bitwidth is ignored for real
			"real_val",
			/*alias handle =*/0
		),
		1u
	);

	// Get the hierarchy buffer content
	string buf = GetHierarchyBuffer(Writer);
	// For eVcdReal, bitwidth should be encoded as 8 bytes (64 bits)
	// Type: 0x1a, Direction: 0x01, Name: "real_val", bitwidth: 0x08,  Alias: 0x00
	string expected = "\x03\x01real_val\x00\x08\x00"s;
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferNormalVar) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_WIRE,
			fst::Hierarchy::VarDirection::INPUT,
			/*bitwidth =*/15,
			"data",
			/*alias handle =*/0
		),
		1u
	);
	string buf = GetGeometryBuffer(Writer);
	string expected = "\x0f"s;
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferRealVar) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_REAL,
			fst::Hierarchy::VarDirection::INPUT,
			/*bitwidth =*/0,
			"real_data",
			/*alias handle =*/0
		),
		1u
	);
	string buf = GetGeometryBuffer(Writer);
	string expected = "\x00"s;
	EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferZerobitwidthVar) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	EXPECT_EQ(
		Writer.createVar(
			fst::Hierarchy::VarType::VCD_WIRE,
			fst::Hierarchy::VarDirection::INPUT,
			/*bitwidth =*/0,
			"zero",
			/*alias handle =*/0
		),
		1u
	);
	string buf = GetGeometryBuffer(Writer);
	// leb128 encoding of 0xffffffff
	string expected = "\xFF\xFF\xFF\xFF\x0F"s;
	EXPECT_EQ(buf, expected);
}

////////////////////////////////////////////////
// Tests for Blackout
////////////////////////////////////////////////
TEST_F(WriterTest, writeBlackout_Short) {
	Writer Writer;
	Writer.setWriterPackType(WriterPackType::NO_COMPRESSION);
	// 1. Blackout between 10 to 20
	Writer.emitTimeChange(10);
	Writer.emitDumpActive(false);
	Writer.emitTimeChange(20);
	Writer.emitDumpActive(true);
	// Check output
	std::string ss(9, '\0');  // need some buffer to allow AppendBlackout to seek
	std::stringstream os(ss);
	appendBlackout(Writer, os);
	std::string out = os.str();

	// Verify block type and size
	EXPECT_EQ(static_cast<uint8_t>(out[0]), static_cast<uint8_t>(BlockType::BLACKOUT));
	// block size field (8 bytes, big-endian) contains value of 13
	EXPECT_EQ(out.substr(1, 8), "\x00\x00\x00\x00\x00\x00\x00\x0d"s);
	// Next 5 bytes: 0x04 0x00 0x0a 0x01 0x14
	EXPECT_EQ(out.substr(9, 5), "\x04\x00\x0a\x01\x14"s);
}

////////////////////////////////////////////////
// Tests for writeHeader
////////////////////////////////////////////////
TEST_F(WriterTest, writeHeader) {
	// 1. setup Header struct manually with unique values
	Header h_struct;
	h_struct.start_time = 10;
	h_struct.end_time = 1000;
	h_struct.writer_memory_use = 4096;
	h_struct.num_scopes = 5;
	h_struct.num_vars = 42;
	h_struct.num_handles = 100;
	h_struct.num_value_change_data_blocks = 3;
	h_struct.timezero = 123456789;
	h_struct.timescale = -9;
	h_struct.filetype = FileType::VERILOG;

	const string writer_name = "Verilator FST Writer Test";
	// safe copy
	const auto wlen = min(writer_name.size(), sizeof(h_struct.writer));
	copy_n(writer_name.data(), wlen, h_struct.writer);
	if (wlen < sizeof(h_struct.writer)) h_struct.writer[wlen] = '\0';

	// Date must be exactly 25 chars (asctime format with \n)
	const string date_str = "Fri Dec 13 01:21:40 2024\n";
	const auto dlen = min(date_str.size(), sizeof(h_struct.date));
	copy_n(date_str.data(), dlen, h_struct.date);
	// note: date is not null terminated in struct if full, but our test string
	// fits with null if we want
	if (dlen < sizeof(h_struct.date)) h_struct.date[dlen] = '\0';

	// 2. Call static writeHeader_ to stringstream
	ostringstream os;
	writeHeader(h_struct, os);

	// 3. Generate Golden Reference
	std::vector<uint8_t> expected_vec;
	StreamVectorwriteHelper h(expected_vec);

	// Helper to pad strings with nulls
	auto write_padded = [&](const string &s, size_t len) {
		size_t n = min(s.size(), len);
		if (n > 0) h.writeString(make_string_view_pair(s.data(), n));
		if (len > n) h.fill<char>(0, len - n);
	};

	h.writeBlockHeader(BlockType::HEADER, HeaderInfo::total_size)
		.writeUIntBE(uint64_t(10))    // start_time
		.writeUIntBE(uint64_t(1000))  // end_time
		.write(HeaderInfo::kEndianessMagicIdentifier)
		.writeUIntBE(uint64_t(4096))  // Writer_memory_use
		.writeUIntBE(uint64_t(5))     // num_scopes
		.writeUIntBE(uint64_t(42))    // num_vars
		.writeUIntBE(uint64_t(100))   // num_handles
		.writeUIntBE(uint64_t(3))     // num_value_change_data_blocks
		.writeUIntBE(int8_t(-9));     // timescale

	write_padded(writer_name, sizeof(h_struct.writer));
	write_padded(date_str, sizeof(h_struct.date));

	h.fill<char>(0, HeaderInfo::Size::reserved)                // reserved
		.writeUIntBE(static_cast<uint8_t>(FileType::VERILOG))  // filetype (default)
		.writeUIntBE(int64_t(123456789));                      // timezero

	// 4. Compare
	// Since stream includes binary 0s, we compare underlying strings
	std::string expected_str(expected_vec.begin(), expected_vec.end());
	EXPECT_EQ(os.str().size(), expected_str.size());
	EXPECT_EQ(os.str(), expected_str);
}

}  // namespace fst
