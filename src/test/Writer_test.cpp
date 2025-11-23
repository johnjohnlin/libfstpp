#include <gtest/gtest.h>
#include "fstcpp/Writer.hpp"

namespace fst {

class WriterTest : public ::testing::Test {
protected:
	void SetUp() override {
		// Setup Writer instance
        writer = std::unique_ptr<fst::Writer>(new fst::Writer(ss));
	}

	std::unique_ptr<fst::Writer> writer;
	std::ostringstream ss;
};

TEST_F(WriterTest, InitializeWithStringStream) {
	ASSERT_TRUE(writer != nullptr);
	SUCCEED();
}

} // namespace fst