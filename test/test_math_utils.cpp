#include "math_utils.h"
#include <gtest/gtest.h>

// Test case for the add function
TEST(MathUtilsTest, AddFunction)
{
    EXPECT_EQ(add(1, 1), 2);
    EXPECT_EQ(add(-1, 1), 0);
    EXPECT_EQ(add(-1, -1), -2);
    EXPECT_EQ(add(0, 0), 0);
}

// Run all the tests
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
