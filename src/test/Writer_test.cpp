#include <gtest/gtest.h>
#include "fstcpp/Writer.hpp"

using namespace std;

namespace fst {

class WriterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup Writer instance
        writer = unique_ptr<fst::Writer>(new fst::Writer(ss));
    }

    const string get_hierarchy_buffer() {
        return writer->hierarchy_buffer_.str();
    }

    unique_ptr<fst::Writer> writer;
    ostringstream ss;
};

TEST_F(WriterTest, DISABLED_CreateVar) {
    // Call CreateVar
    EXPECT_EQ(writer->CreateVar(
        fst::Hierarchy::VarType::eVcdWire,
        fst::Hierarchy::VarDirection::eFstInput,
        /*length =*/8,
        "valid",
        /*alias handle =*/0
    ), 1u);

    // Second Call CreateVar
    EXPECT_EQ(writer->CreateVar(
        fst::Hierarchy::VarType::eVcdPort,
        fst::Hierarchy::VarDirection::eFstOutput,
        /*length =*/5566,
        "ready",
        /*alias handle =*/0
    ), 2u);

    // Get the hierarchy buffer content
    string buf = get_hierarchy_buffer();
    // expected: Type, Direction, Name, Length, Alias Handle
    // FIXME: in fstapi.c:2598 it writes len, zero, zero for normal variable this may be a bug
    string expected = "\x10\x01valid\x00\x08\x00"s \
        "\x12\x02ready\x00\xbe\x2b\x00"s;
    EXPECT_EQ(buf, expected);
}

} // namespace fst