#include "../src/Bullet.h"
#include <gtest/gtest.h>

Bullet bullet = Bullet(Vector2(), Vector2(), CollisionCircle());

TEST(Bullet, constructor)
{
    Vector2 someValue(17.0f, 17.0f);
    int speedTestValue = 17;

    Bullet testInstance = Bullet(
            someValue,
            someValue,
            CollisionCircle(someValue),
            someValue,
            speedTestValue
            );

    EXPECT_EQ(someValue, testInstance.position);
    EXPECT_EQ(Vector2(1.0f, 1.0f), testInstance.direction);
    EXPECT_EQ(Vector2(34.0f, 34.0f), testInstance.collision_circle.origin);
    EXPECT_EQ(someValue, testInstance.scale);
    EXPECT_EQ(speedTestValue, testInstance.speed);
}

TEST(Bullet, move)
{
    Bullet bullet1 = Bullet(Vector2(), Vector2(), CollisionCircle());
    float delta = 0.015f;
    bullet1.direction = Vector2(1.0f, 1.0f);
    bullet1.move(delta);


    ASSERT_TRUE(bullet.position.x < bullet1.position.x);
    ASSERT_TRUE(bullet.position.y < bullet1.position.y);
    ASSERT_TRUE(bullet.collision_circle.origin.x < bullet1.collision_circle.origin.x);
    ASSERT_TRUE(bullet.collision_circle.origin.y < bullet1.collision_circle.origin.y);


}
