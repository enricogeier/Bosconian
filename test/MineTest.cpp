#include "../src/Mine.h"
#include <gtest/gtest.h>

TEST(Mine, explode)
{
    Mine mine = Mine(Vector2(1.0f, 1.0f), CollisionCircle());
    Vector2 initial_origin = mine.collision_circle.initial_origin;

    mine.explode();

    EXPECT_TRUE(mine.position.x != 1.0f);
    EXPECT_TRUE(mine.position.y != 1.0f);
    EXPECT_TRUE(initial_origin.x != mine.collision_circle.initial_origin.x);
    EXPECT_TRUE(initial_origin.y != mine.collision_circle.initial_origin.y);

}