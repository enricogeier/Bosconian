#include "../src/Vector2.h"
#include <gtest/gtest.h>


TEST(Vector2, equal)
{
    Vector2 instance0 = Vector2(17.0f, 17.0f);
    Vector2 instance1 = instance0;

    EXPECT_EQ(instance0, instance1);

}

TEST(Vector2, notEqual)
{
    Vector2 instance0 = Vector2(17.0f, 17.0f);
    Vector2 instance1;

    EXPECT_NE(instance0, instance1);
}

TEST(Vector2, plus)
{
    Vector2 v0 = Vector2(1.0f, 1.0f);
    Vector2 v1 = v0 + Vector2(16.0f, 16.0f);

    EXPECT_EQ(v1, Vector2(17.0f, 17.0f));
}

TEST(Vector2, minus)
{
    Vector2 v0 = Vector2(20.0f, 20.0f);
    Vector2 v1 = v0 - Vector2(3.0f, 3.0f);

    EXPECT_EQ(v1, Vector2(17.0f, 17.0f));
}

TEST(Vector2, star)
{
    Vector2 v0 = Vector2(1.0f, 1.0f);
    Vector2 v1 = Vector2(-1.0f, 1.0f);

    EXPECT_FLOAT_EQ(v0 * v1, 0);

}

TEST(Vector2, s2)
{
    float factor = 2.0f;
    Vector2 v0 = Vector2(2.0f, 2.0f);

    EXPECT_EQ(v0 * factor, Vector2(4.0f, 4.0f));
}

TEST(Vector2, distance)
{
    Vector2 v0 = Vector2(18.0f, 18.0f);
    Vector2 v1 = Vector2(17.0f, 18.0f);

    EXPECT_EQ(Vector2::distance(v0, v1), 1);
}


TEST(Vector2, clamp)
{
    Vector2 result = Vector2(4.0f, 6.0f).clamp();

    EXPECT_FLOAT_EQ(result.x, 0.554700196);
    EXPECT_FLOAT_EQ(result.y, 0.832050323);

}

