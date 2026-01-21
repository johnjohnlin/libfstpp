// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
// direct include
#include "fstcpp/Writer.cpp"
#include "fstcpp/fst.h"
// C system headers
// C++ standard library headers
#include <cstring>
// Other libraries' .h files.
#include <gtest/gtest.h>
// Your project's .h files.

using namespace std;

namespace fst {

constexpr unsigned kDontCareBitWidth = 1234;

/////////////////////////////
// WriteInitialBits
/////////////////////////////
TEST(VariableInfoTest, WriteInitialBits_ScalarInt) {
    VariableInfo vi(4);
    vi.EmitValueChange(0, 0b1010);
    vi.KeepOnlyTheLatestValue();
    ostringstream os;
    vi.DumpInitialBits(os);
    EXPECT_EQ(os.str(), "1010");
}

TEST(VariableInfoTest, WriteInitialBits_LongInt) {
    VariableInfo vi(70);
    vi.EmitValueChange(0, (1ULL << 63) | 1);
    vi.KeepOnlyTheLatestValue();
    ostringstream os;
    vi.DumpInitialBits(os);
    // Should be 70 bits: 1 at bit 63 and bit 0, rest are 0
    string expected = string(6, '0') + "1" + string(62, '0') + "1";
    EXPECT_EQ(os.str(), expected);
}

TEST(VariableInfoTest, WriteInitialBits_Double) {
    VariableInfo vi(kDontCareBitWidth, true);
    vi.EmitValueChange(0, 0x3ff0000000000000ULL); // 1.0 in IEEE754
    vi.KeepOnlyTheLatestValue();
    ostringstream os;
    vi.DumpInitialBits(os);
    double val;
    string s = os.str();
    memcpy(&val, s.data(), sizeof(double));
    EXPECT_DOUBLE_EQ(val, 1.0);
}

/////////////////////////////
// EmitValueChange
/////////////////////////////
TEST(VariableInfoTest, EmitValueChange_Double_Array32) {
    VariableInfo vi(32, true); // 32 bits, double type
    uint64_t dummy_buf = 0x3ff00000ULL;
    EXPECT_THROW(
        vi.EmitValueChange(0, reinterpret_cast<uint32_t *>(&dummy_buf), EncodingType::eBinary), std::runtime_error);
}

TEST(VariableInfoTest, EmitValueChange_Double_Array64) {
    VariableInfo vi(64, true); // 64 bits, double type
    uint64_t dummy_buf = 0x3ff0000000000000ULL;
    EXPECT_THROW(
        vi.EmitValueChange(0, reinterpret_cast<uint64_t *>(&dummy_buf), EncodingType::eBinary), std::runtime_error);
}

/////////////////////////////
// DumpValueChanges
/////////////////////////////
TEST(VariableInfoTest, DumpValueChange_ScalarInt_1bit_Binary) {
    VariableInfo vi(1);
    vi.EmitValueChange(1, 0);
    vi.EmitValueChange(2, 1);
    vi.EmitValueChange(3, 0);
    ostringstream os;
    vi.DumpValueChanges(os);
    // Encoding time_index_delta << 2 | (bit << 1) | 0 in binary mode
    // (1-0) << 2 | 0b00
    // (2-1) << 2 | 0b10
    // (3-2) << 2 | 0b00
    EXPECT_EQ(os.str(), "\x04\x06\x04"s);
}

TEST(VariableInfoTest, DumpValueChange_ScalarInt_2bit_Binary) {
    VariableInfo vi(2);
    vi.EmitValueChange(1, 0);
    vi.EmitValueChange(3, 1);
    vi.EmitValueChange(5, 2);
    vi.EmitValueChange(7, 3);
    vi.EmitValueChange(10, 0);
    ostringstream os;
    vi.DumpValueChanges(os);
    // 1. Varint encoding of (Time_index_delta << 1) | 0
    // 2. data encoded as raw bits,aligned with MSB and packed into a whole number of bytes
    EXPECT_EQ(os.str(), "\x02\x00\x04\x40\x04\x80\x04\xc0\x06\x00"s);
}

TEST(VariableInfoTest, DumpValueChange_ScalarInt_10bit_Binary) {
    VariableInfo vi(10);
    vi.EmitValueChange(1, 0);
    vi.EmitValueChange(3, 1);
    vi.EmitValueChange(5, 2);
    vi.EmitValueChange(7, 4);
    vi.EmitValueChange(10, 8);
    ostringstream os;
    vi.DumpValueChanges(os);
    // 1. Varint encoding of Time_index_delta << 1 | 1 since it contains only 0 and 1
    // 2. data encoded as raw bits,aligned with MSB and packed into a whole number of bytes
    EXPECT_EQ(os.str(), "\x02\x00\x00"
                        "\x04\x00\x40"
                        "\x04\x00\x80"
                        "\x04\x01\x00"
                        "\x06\x02\x00"s);
}

TEST(VariableInfoTest, DumpValueChange_LongInt_Binary) {
    VariableInfo vi(68);
    vi.EmitValueChange(2, 0);
    vi.EmitValueChange(5, 0x1234567890abcdefULL);
    ostringstream os;
    vi.DumpValueChanges(os);
    EXPECT_EQ(os.str(), "\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                        "\x06\x01\x23\x45\x67\x89\x0a\xbc\xde\xf0"s);
}

// LCOV_EXCL_START
TEST(VariableInfoTest, DISABLED_DumpValueChange_Double_Binary) {
    VariableInfo vi(kDontCareBitWidth, true);
    vi.EmitValueChange(0, 0x3ff0000000000000ULL); // 1.0 in IEEE754
    ostringstream os;
    vi.DumpValueChanges(os);
    FAIL() << "TODO";
}
// LCOV_EXCL_STOP

} // namespace fst
