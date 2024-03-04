#include "../src/Bullet.h"
#include <gtest/gtest.h>

Bullet bullet = Bullet(Vector2(), Vector2(), CollisionCircle());

TEST(Bullet, increment)
{
    int a = 5;

    bullet.increment(a);
    EXPECT_EQ(a, 6);

}

