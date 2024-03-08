#include "../src/Enemy.h"
#include <gtest/gtest.h>

TEST(Enemy, move1)
{
    Enemy enemy = Enemy(Vector2(), CollisionCircle());

    Vector2 playerPosition = Vector2(1717.0f, 0.0f);
    float delta = 0.000001f;
    enemy.move(playerPosition, delta);

    EXPECT_NE(Vector2(), enemy.position);
    EXPECT_TRUE(enemy.position.x > 0.0f);

    while(playerPosition.x - enemy.position.x > 0.0f)
    {
        enemy.move(playerPosition, delta);
    }

    EXPECT_FLOAT_EQ(enemy.position.x, playerPosition.x);

}

TEST(Enemy, move2)
{
    Enemy enemy = Enemy(Vector2(), CollisionCircle());

    Vector2 playerPosition = Vector2(171.0f, 171.0f);
    float delta = 0.0000001f;
    enemy.move(playerPosition, delta);

    EXPECT_NE(Vector2(), enemy.position);
    EXPECT_TRUE(enemy.position.x > 0.0f);

    while(playerPosition.x - enemy.position.x > 0.0f)
    {
        enemy.move(playerPosition, delta);
    }

    EXPECT_FLOAT_EQ(enemy.position.x, playerPosition.x);
}