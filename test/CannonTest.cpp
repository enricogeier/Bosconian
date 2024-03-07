#include "../src/Cannon.h"
#include <gtest/gtest.h>

TEST(Cannon, updatePosition)
{
    Cannon instance;

    Vector2 previousPosition = instance.position;
    Vector2 offset = Vector2(17.0f, 17.0f);

    instance.update_position(offset);
    EXPECT_NE(previousPosition, instance.position);

}

TEST(Cannon, checkState)
{
    Cannon c1;
    Cannon c2;


    c1.check_state();

    c2.state = State::EXPLODE;
    c2.check_state();


    EXPECT_EQ(State::NORMAL, c1.state);
    EXPECT_EQ(c2.state, State::DESTROY);


}