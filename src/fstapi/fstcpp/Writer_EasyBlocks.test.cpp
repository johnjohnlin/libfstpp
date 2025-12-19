// direct include
#include "fstcpp/Writer.hpp"
// C system headers
// C++ standard library headers
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sstream>
// Other libraries' .h files.
#include <gtest/gtest.h>
// Your project's .h files.
#include "fstcpp/StreamWriteHelper.hpp"
#include "fstcpp/fst_file.hpp"

using namespace std;

namespace fst {

// This test focus on testing the emit functions of writer
// The name of this test is not unique
// but it is not a problem since Writer_*.test.cpp are individual
// binary files
class WriterTest : public ::testing::Test {
protected:
    // For testing Set(Up)Scope/CreateVar
    // We call writer API and get the buffer content
    // without inspecting the internal state of writer
    static const string GetHierarchyBuffer(Writer& writer) {
        return writer.hierarchy_buffer_.str();
    }

    static const string GetGeometryBuffer(Writer& writer) {
        return writer.geometry_buffer_.str();
    }

    static void WriteHeader(const Header &h, ostream &os) {
        Writer::WriteHeader_(h, os);
    }

    static void AppendBlackout(Writer& writer, std::ostream& os) {
        writer.AppendBlackout_(os);
    }
};

TEST_F(WriterTest, CreateVar) {
    Writer writer;
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
    string buf = GetHierarchyBuffer(writer);
    // expected: Type, Direction, Name, bitwidth, Alias Handle
    // FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
    string expected = "\x10\x01valid\x00\x08\x00"s \
        "\x12\x02ready\x00\xbe\x2b\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, CreateVarAlias) {
    Writer writer;
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
    string buf = GetHierarchyBuffer(writer);
    // expected: Type, Direction, Name, bitwidth, Alias Handle
    // FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
    string expected = "\x10\x01" "clk\x00\x01\x00"s \
                      "\x12\x02" "aliasclk\x00\x0d\x01"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, CreateAliasOutOfRange) {
    Writer writer;
    // Call CreateVar
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/16,
        "mode",
        /*alias handle =*/0
    ), 1u);

    // Get the hierarchy buffer content
    string buf = GetHierarchyBuffer(writer);
    // expected: Type, Direction, Name, bitwidth, Alias Handle
    // FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
    string expected = "\x10\x01mode\x00\x10\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, Scope) {
    Writer writer;
    // Set Scope
    writer.SetScope(
        fst::Hierarchy::ScopeType::eVcdModule,
        "top",
        "component"); // TODO: what is this?
    writer.Upscope();

    // Get the hierarchy buffer content
    string buf = GetHierarchyBuffer(writer);
    // expected: Scope Type, Name, component, Upscope
    string expected = "\xfe\x00top\x00" "component\x00" \
                      "\xff"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, CreateVarVcdReal) {
    Writer writer;
    // Call CreateVar with eVcdReal
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdReal,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/0, // bitwidth is ignored for real
        "real_val",
        /*alias handle =*/0
    ), 1u);

    // Get the hierarchy buffer content
    string buf = GetHierarchyBuffer(writer);
    // For eVcdReal, bitwidth should be encoded as 8 bytes (64 bits)
    // Type: 0x1a, Direction: 0x01, Name: "real_val", bitwidth: 0x08,  Alias: 0x00
    string expected = "\x03\x01real_val\x00\x08\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferNormalVar) {
    Writer writer;
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/15,
        "data",
        /*alias handle =*/0
    ), 1u);
    string buf = GetGeometryBuffer(writer);
    string expected = "\x0f"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferRealVar) {
    Writer writer;
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdReal,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/0,
        "real_data",
        /*alias handle =*/0
    ), 1u);
    string buf = GetGeometryBuffer(writer);
    string expected = "\x00"s;
    EXPECT_EQ(buf, expected);
}

TEST_F(WriterTest, GeometryBufferZerobitwidthVar) {
    Writer writer;
    EXPECT_EQ(writer.CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eInput,
        /*bitwidth =*/0,
        "zero",
        /*alias handle =*/0
    ), 1u);
    string buf = GetGeometryBuffer(writer);
    // leb128 encoding of 0xffffffff
    string expected = "\xFF\xFF\xFF\xFF\x0F"s;
    EXPECT_EQ(buf, expected);
}

////////////////////////////////////////////////
// Tests for Blackout
////////////////////////////////////////////////
TEST_F(WriterTest, WriteBlackout_Short) {
    Writer writer;
    // 1. Blackout between 10 to 20
    writer.EmitTimeChange(10);
    writer.EmitDumpActive(false);
    writer.EmitTimeChange(20);
    writer.EmitDumpActive(true);
    // Check output
    std::string ss(9, '\0'); // need some buffer to allow AppendBlackout to seek
    std::stringstream os(ss);
    AppendBlackout(writer, os);
    std::string out = os.str();

    // Verify block type and size
    EXPECT_EQ(static_cast<uint8_t>(out[0]), static_cast<uint8_t>(BlockType::Blackout));
    // block size field (8 bytes, big-endian) contains value of 13
    EXPECT_EQ(out.substr(1, 8), "\x00\x00\x00\x00\x00\x00\x00\x0d"s);
    // Next 5 bytes: 0x04 0x00 0x0a 0x01 0x14
    EXPECT_EQ(out.substr(9, 5), "\x04\x00\x0a\x01\x14"s);
}

////////////////////////////////////////////////
// Tests for WriteHeader
////////////////////////////////////////////////
TEST_F(WriterTest, WriteHeader) {
    // 1. Setup Header struct manually with unique values
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
    h_struct.filetype = FileType::eVerilog;

    const string writer_name = "Verilator FST Writer Test";
    // safe copy
    const auto wlen = min(writer_name.size(), sizeof(h_struct.writer));
    copy_n(writer_name.data(), wlen, h_struct.writer);
    if (wlen < sizeof(h_struct.writer))
        h_struct.writer[wlen] = '\0';

    // Date must be exactly 25 chars (asctime format with \n)
    const string date_str = "Fri Dec 13 01:21:40 2024\n";
    const auto dlen = min(date_str.size(), sizeof(h_struct.date));
    copy_n(date_str.data(), dlen, h_struct.date);
    // note: date is not null terminated in struct if full, but our test string
    // fits with null if we want
    if (dlen < sizeof(h_struct.date))
        h_struct.date[dlen] = '\0';

    // 2. Call static WriteHeader_ to stringstream
    ostringstream os;
    WriteHeader(h_struct, os);

    // 3. Generate Golden Reference
    ostringstream expected_os;
    StreamWriteHelper h(expected_os);

    // Helper to pad strings with nulls
    auto write_padded = [&](const string &s, size_t len) {
        vector<char> buf(len, 0);
        if (not s.empty()) {
            memcpy(buf.data(), s.data(), min(s.size(), len));
        }
        h.Write(buf.data(), len);
    };

    h
    .WriteBlockHeader(BlockType::Header, HeaderInfo::total_size)
    .WriteUInt(uint64_t(10))   // start_time
    .WriteUInt(uint64_t(1000)) // end_time
    .WriteFloat(HeaderInfo::kEndianessMagicIdentifier)
    .WriteUInt(uint64_t(4096)) // writer_memory_use
    .WriteUInt(uint64_t(5))    // num_scopes
    .WriteUInt(uint64_t(42))   // num_vars
    .WriteUInt(uint64_t(100))  // num_handles
    .WriteUInt(uint64_t(3))    // num_value_change_data_blocks
    .WriteUInt(int8_t(-9));    // timescale

    write_padded(writer_name, sizeof(h_struct.writer));
    write_padded(date_str, sizeof(h_struct.date));

    h
    .Fill('\0', HeaderInfo::Size::reserved)
    .WriteUInt(static_cast<uint8_t>(FileType::eVerilog)) // filetype (default)
    .WriteUInt(int64_t(123456789));                      // timezero

    // 4. Compare
    // Since stream includes binary 0s, we compare underlying strings
    EXPECT_EQ(os.str().size(), expected_os.str().size());
    EXPECT_EQ(os.str(), expected_os.str());
}

} // namespace fst
