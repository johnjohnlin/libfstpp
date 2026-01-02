// direct include
#include "fstcpp/Writer.cpp"
// C system headers
// C++ standard library headers
#include <cstring>
// Other libraries' .h files.
#include <gtest/gtest.h>
// Your project's .h files.

using namespace std;

namespace fst {

using VariableInfoBase = detail::ValueChangeData::VariableInfoBase;
constexpr unsigned kDontCareBitWidth = 1234;

TEST(VariableInfoTest, Create) {
    // int
    std::unique_ptr<VariableInfoBase> vi_int(VariableInfoBase::Create(8, false));
    EXPECT_NE(vi_int, nullptr);
    // Should be VariableInfoScalarInt<uint8_t>
    auto* vi_int_cast = dynamic_cast<fst::detail::VariableInfoScalarInt<uint8_t>*>(vi_int.get());
    EXPECT_NE(vi_int_cast, nullptr);

    // long
    std::unique_ptr<VariableInfoBase> vi_long(VariableInfoBase::Create(128, false));
    EXPECT_NE(vi_long, nullptr);
    // Should be VariableInfoLongInt
    auto* vi_long_cast = dynamic_cast<fst::detail::VariableInfoLongInt*>(vi_long.get());
    EXPECT_NE(vi_long_cast, nullptr);

    // double
    std::unique_ptr<VariableInfoBase> vi_double(VariableInfoBase::Create(kDontCareBitWidth, true));
    EXPECT_NE(vi_double, nullptr);
    // Should be VariableInfoDouble
    auto* vi_double_cast = dynamic_cast<fst::detail::VariableInfoDouble*>(vi_double.get());
    EXPECT_NE(vi_double_cast, nullptr);
}
/////////////////////////////
// WriteInitialBits
/////////////////////////////
TEST(VariableInfoTest, WriteInitialBits_ScalarInt) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(4, false));
    vi->EmitValueChange(0, 0b1010);
    vi->KeepOnlyTheLatestValue();
    std::ostringstream os;
    vi->DumpInitialBits(os);
    EXPECT_EQ(os.str(), "1010");
}

TEST(VariableInfoTest, WriteInitialBits_LongInt) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(70, false));
    vi->EmitValueChange(0, (1ULL << 63) | 1);
    vi->KeepOnlyTheLatestValue();
    std::ostringstream os;
    vi->DumpInitialBits(os);
    // Should be 70 bits: 1 at bit 63 and bit 0, rest are 0
    std::string expected = std::string(6, '0') + "1" + std::string(62, '0') + "1";
    EXPECT_EQ(os.str(), expected);
}

TEST(VariableInfoTest, WriteInitialBits_Double) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(kDontCareBitWidth, true));
    vi->EmitValueChange(0, 0x3ff0000000000000ULL); // 1.0 in IEEE754
    vi->KeepOnlyTheLatestValue();
    std::ostringstream os;
    vi->DumpInitialBits(os);
    double val;
    std::string s = os.str();
    memcpy(&val, s.data(), sizeof(double));
    EXPECT_DOUBLE_EQ(val, 1.0);
}
/////////////////////////////
// DumpValueChanges
/////////////////////////////
TEST(VariableInfoTest, DumpValueChange_ScalarInt_1bit_Binary) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(1, false));
    vi->EmitValueChange(1, 0);
    vi->EmitValueChange(2, 1);
    vi->EmitValueChange(3, 0);
    std::ostringstream os;
    vi->DumpValueChanges(os);
    // Encoding time_index_delta << 2 | (bit << 1) | 0 in binary mode
    // (1-0) << 2 | 0b00
    // (2-1) << 2 | 0b10
    // (3-2) << 2 | 0b00
    EXPECT_EQ(os.str(), "\x04\x06\x04"s);
}

TEST(VariableInfoTest, DumpValueChange_ScalarInt_2bit_Binary) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(2, false));
    vi->EmitValueChange(1, 0);
    vi->EmitValueChange(3, 1);
    vi->EmitValueChange(5, 2);
    vi->EmitValueChange(7, 3);
    vi->EmitValueChange(10, 0);
    std::ostringstream os;
    vi->DumpValueChanges(os);
    // 1. Varint encoding of (Time_index_delta << 1) | 0
    // 2. data encoded as raw bits,aligned with MSB and packed into a whole number of bytes
    EXPECT_EQ(os.str(), "\x02\x00\x04\x40\x04\x80\x04\xc0\x06\x00"s);
}

TEST(VariableInfoTest, DumpValueChange_ScalarInt_10bit_Binary) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(10, false));
    vi->EmitValueChange(1, 0);
    vi->EmitValueChange(3, 1);
    vi->EmitValueChange(5, 2);
    vi->EmitValueChange(7, 4);
    vi->EmitValueChange(10, 8);
    std::ostringstream os;
    vi->DumpValueChanges(os);
    // 1. Varint encoding of Time_index_delta << 1 | 1 since it contains only 0 and 1
    // 2. data encoded as raw bits,aligned with MSB and packed into a whole number of bytes
    EXPECT_EQ(os.str(), "\x02\x00\x00"
                        "\x04\x00\x40"
                        "\x04\x00\x80"
                        "\x04\x01\x00"
                        "\x06\x02\x00"s);
}

TEST(VariableInfoTest, DumpValueChange_LongInt_Binary) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(68, false));
    vi->EmitValueChange(2, 0);
    vi->EmitValueChange(5, 0x1234567890abcdefULL);
    std::ostringstream os;
    vi->DumpValueChanges(os);
    EXPECT_EQ(os.str(), "\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                        "\x06\x01\x23\x45\x67\x89\x0a\xbc\xde\xf0"s);
}

// LCOV_EXCL_START
TEST(VariableInfoTest, DISABLED_DumpValueChange_Double_Binary) {
    std::unique_ptr<VariableInfoBase> vi(VariableInfoBase::Create(kDontCareBitWidth, true));
    vi->EmitValueChange(0, 0x3ff0000000000000ULL); // 1.0 in IEEE754
    std::ostringstream os;
    vi->DumpValueChanges(os);
    FAIL() << "TODO";
}
// LCOV_EXCL_STOP

} // namespace fst
