// gtestDemo.cpp
// ABR 20131019
#include "gtest/gtest.h"

namespace /* give a hoot */ {

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

static void assertInFunction() {
    ASSERT_FALSE(true)
    << std::endl << "Don't assert in functions" << std::endl;

    assert(not "going to finish this function");    
}

TEST(DemoTest,AssertInFunction)
{
    assertInFunction();
    ASSERT_TRUE(not "supposed to reach this line")
    << std::endl
    << "The previous assertion failed to abort the test." << std::endl
    << "This could lead to difficult-to-diagnose errors." << std::endl;

    assert(not "supposed to finish the suite");
}

} // don't pollute