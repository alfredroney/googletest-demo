#include "gtest/gtest.h"

TEST(DemoTest,PassingAssert)
{
    ASSERT_TRUE(true)
    << "This message should not be written to the console." << std::endl;
}

TEST(DemoTest,FailingAsert)
{
    ASSERT_TRUE(not true)
    << "This message should be written to the console." << std::endl;
}

TEST(DemoTest,PassAndFailingExpect)
{
    EXPECT_TRUE(true)
    << "This message should not be written to the console." << std::endl;
    EXPECT_TRUE(not true)
    << "This message should be written to the console." << std::endl;
    EXPECT_TRUE(not true)
    << "This message should also be written to the console." << std::endl;
}
