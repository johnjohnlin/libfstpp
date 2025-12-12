// direct include
#include "fstcpp/Writer.hpp"
// C system headers
// C++ standard library headers
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <numeric>
#include <iostream>
#include <sstream>
// Other libraries' .h files.
#include <gtest/gtest.h>
// Your project's .h files.

using namespace std;

namespace fst {

class WriterTest : public ::testing::Test {
protected:
    void SetUp() override {}

    const string get_hierarchy_buffer() {
        return writer.hierarchy_buffer_.str();
    }

    const string get_geometry_buffer() {
        return writer.geometry_buffer_.str();
    }

    // For testing internal function FlushValueChangeData_Timestamps_
    string FlushValueChangeData_Timestamps_(vector<uint64_t>& timestamps) {
        writer.value_change_data_.timestamps = timestamps;
        ostringstream os;
        writer.FlushValueChangeData_Timestamps_(os);
        return os.str();
    }

    Writer writer;
    ostringstream ss;
};

TEST_F(WriterTest, CreateVar) {
    // Call CreateVar
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/8,
        "valid",
        /*alias handle =*/0
    ), 1u);

    // Second Call CreateVar
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdPort,
        fst::Hierarchy::VarDirection::eOutput,
        /*bitwidth =*/5566,
        "ready",
        /*alias handle =*/0
    ), 2u);

    // Get the hierarchy buffer content
    string buf = get_hierarchy_buffer();
    // expected: Type, Direction, Name, bitwidth, Alias Handle
    // FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
    string expected = "\x10\x01valid\x00\x08\x00"s \
        "\x12\x02ready\x00\xbe\x2b\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, CreateVarAlias) {
    // Call CreateVar
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/1,
        "clk",
        /*alias handle =*/0
    ), 1u);

    // Second Call CreateVar
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdPort,
        fst::Hierarchy::VarDirection::eOutput,
        /*bitwidth =*/0xd, // don't care
        "aliasclk",
        /*alias handle =*/1
    ), 1u);

    // Get the hierarchy buffer content
    string buf = get_hierarchy_buffer();
    // expected: Type, Direction, Name, bitwidth, Alias Handle
    // FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
    string expected = "\x10\x01" "clk\x00\x01\x00"s \
                      "\x12\x02" "aliasclk\x00\x0d\x01"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, CreateAliasOutOfRange) {
    // Call CreateVar
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/16,
        "mode",
        /*alias handle =*/0
    ), 1u);

    // Get the hierarchy buffer content
    string buf = get_hierarchy_buffer();
    // expected: Type, Direction, Name, bitwidth, Alias Handle
    // FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
    string expected = "\x10\x01mode\x00\x10\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, Scope) {
    // Set Scope
    writer.SetScope(
        fst::Hierarchy::ScopeType::eVcdModule,
        "top",
        "component"); // TODO: what is this?
    writer.Upscope();

    // Get the hierarchy buffer content
    string buf = get_hierarchy_buffer();
    // expected: Scope Type, Name, component, Upscope
    string expected = "\xfe\x00top\x00" "component\x00" \
                      "\xff"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, CreateVarVcdReal) {
    // Call CreateVar with eVcdReal
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdReal,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/0, // bitwidth is ignored for real
        "real_val",
        /*alias handle =*/0
    ), 1u);

    // Get the hierarchy buffer content
    string buf = get_hierarchy_buffer();
    // For eVcdReal, bitwidth should be encoded as 8 bytes (64 bits)
    // Type: 0x1a, Direction: 0x01, Name: "real_val", bitwidth: 0x08,  Alias: 0x00
    string expected = "\x03\x01real_val\x00\x08\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferNormalVar) {
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/15,
        "data",
        /*alias handle =*/0
    ), 1u);
    string buf = get_geometry_buffer();
    string expected = "\x0f"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferRealVar) {
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdReal,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/0,
        "real_data",
        /*alias handle =*/0
    ), 1u);
    string buf = get_geometry_buffer();
    string expected = "\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferZerobitwidthVar) {
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/0,
        "zero",
        /*alias handle =*/0
    ), 1u);
    string buf = get_geometry_buffer();
    // leb128 encoding of 0xffffffff
    string expected = "\xFF\xFF\xFF\xFF\x0F"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, FlushValueChangeData_Timestamps) {
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

    string result = FlushValueChangeData_Timestamps_(timestamps);
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
    EXPECT_EQ(result, expected);
}

} // namespace fst
