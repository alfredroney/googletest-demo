#include "gtest/gtest.h"

class FixtureDemo
: public ::testing::Test
{
protected:

    int d_useCount;

    FixtureDemo()
    : d_useCount { 0 }
    {
        // could do some setup here, but see assertion below
    }

    virtual void SetUp() {
        assert(0==d_useCount);
        std::cout
        << std::endl
        << "Pre-test setup goes here "
        << "(" << ++d_useCount << ")"
        << std::endl;
    }

    virtual void TearDown() {
        std::cout
        << std::endl
        << "Post-test cleanup goes here"
        << std::endl;
    }

    void assertInFixtureMember() {
        // Unfortunately, this technique does not work as expected.
        // The assertion registers a failing test and exits the
        // enclosing function's scope, but *does not* abort the calling case.
        // If this were a null-pointer check on a return-by-reference, the test
        // runner would probably crash.
        //
        // All ASSERT_*() macros from googletest must be called
        // within the scope of the TEST_F(){} block.
        ASSERT_FALSE(true)
        << std::endl
        << "Don't assert in fixture member functions." << std::endl;

        assert(not "going to finish this function");
    }
};

TEST_F(FixtureDemo,PassingAssert)
{
    ASSERT_TRUE(not false) << "Should pass" << std::endl;
}

TEST_F(FixtureDemo,FailingAssert)
{
    ASSERT_FALSE(true)
    << "This message should be written to console" << std::endl;
}

TEST_F(FixtureDemo,AssertInFixtureMember)
{
    assertInFixtureMember();
    ASSERT_TRUE(not "supposed to reach this line")
    << std::endl
    << "The previous assertion failed to abort the test." << std::endl
    << "This could lead to difficult-to-diagnose errors." << std::endl;
    assert(not "supposed to reach this line, either");
}

