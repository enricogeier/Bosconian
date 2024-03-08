#include "../src/Rectangle.h"
#include <gtest/gtest.h>

TEST(Rectangle, Rectangle)
{
    Rectangle instance{1,2,3,4};

    EXPECT_EQ(instance.x, 1);
    EXPECT_EQ(instance.y, 2);
    EXPECT_EQ(instance.w, 3);
    EXPECT_EQ(instance.h, 4);

}