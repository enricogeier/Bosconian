#include "../src/Player.h"
#include <gtest/gtest.h>

TEST(Player, move)
{
    Player instance;

    float delta = 0.05f;
    Vector2 direction = Vector2(17.0f, 17.0f);
    bool accelerate = false;

    instance.move(direction, delta, accelerate);

    EXPECT_NE(Vector2(), instance.direction);
    EXPECT_NE(Player::MAX_VELOCITY, instance.current_velocity);
    EXPECT_NE(Vector2(), instance.position);

}

