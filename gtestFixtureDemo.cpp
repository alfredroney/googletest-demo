// gtestDemoFixture.cpp
// ABR 20131019
#include "gtest/gtest.h"

namespace /* give a hoot */ {

class DemoFixture
: public ::testing::Test
{
protected:

    int d_useCount;

    DemoFixture()
    : d_useCount { 0 }
    {
        // could do some setup here, but see assertion below
    }

    virtual void SetUp() {
        assert(0==d_useCount);
        std::cout
        << std::endl
        << "######## BEGIN TEST ############## "
        << std::endl;
    }

    virtual void TearDown() {
        std::cout
        << std::endl
        << "######## END TEST   ############## "
        << std::endl;
    }

    void assertInFixtureMember() {
        // Unfortunately, this technique does not work as expected.
        // The assertion registers a failing test and exits the
        // enclosing function's scope, but *does not* abort the calling case.
        // Could crash the test runner, preventing other tests from running.
        //
        // All ASSERT_*() macros from googletest must be called
        // within the scope of the TEST_F(){} block if you want them
        // to abort the test case on failure.
        ASSERT_FALSE(true)
        << std::endl
        << "Don't assert in fixture member functions"
        << std::endl;

        assert(not "going to finish executing this function");
    }
}; // class DemoFixture

TEST_F(DemoFixture,PassingAssert)
{
    ASSERT_TRUE(not false) << "Should pass, no console output" << std::endl;
}

TEST_F(DemoFixture,FailingAssert)
{
    ASSERT_FALSE(true)
    << "This message should be written to the console"
    << std::endl;
}

TEST_F(DemoFixture,AssertInFixtureMember)
{
    assertInFixtureMember();
    ASSERT_TRUE(not "supposed to reach this line")
    << std::endl
    << "The previous assertion failed to abort the test." << std::endl
    << "This could lead to difficult-to-diagnose errors." << std::endl;

    assert(not "supposed to reach this line, either");
}

static void assertInFunction() {
    ASSERT_FALSE(true)
    << std::endl << "Don't assert in functions, either." << std::endl;

    assert(not "going to finish this function");    
}

TEST_F(DemoFixture,AssertInFunction)
{
    assertInFunction();
    ASSERT_TRUE(not "supposed to reach this line")
    << std::endl
    << "The previous assertion failed to abort the test." << std::endl
    << "This could lead to difficult-to-diagnose errors." << std::endl;

    assert(not "supposed to reach this line, either");
}

} // don't pollute