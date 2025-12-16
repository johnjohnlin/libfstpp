// direct include
#include "fstcpp/Writer.hpp"
// C system headers
// C++ standard library headers
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <numeric>
#include <sstream>
// Other libraries' .h files.
#include <gtest/gtest.h>
// Your project's .h files.
#include "fstcpp/StreamWriteHelper.hpp"
#include "fstcpp/fst_file.hpp"

using namespace std;

namespace fst {

// This test focuses on testing the emit functions of writer
// The name of this test is not unique
// but it is not a problem since Writer_*.test.cpp are individual
// binary files
class WriterTest : public ::testing::Test {
protected:
};

TEST_F(WriterTest, TODO) {
}

} // namespace fst
