#include "../src/CollisionCircle.h"
#include <gtest/gtest.h>

TEST(CollisionCirlce, equalFunction)
{
    CollisionCircle c1 = CollisionCircle(
            Vector2(17.0f, 17.0f),
            17.0f,
            Layer::CELESTIAL_OBJECT,
            {}
            );

    CollisionCircle c2 = c1;

    EXPECT_EQ(c1.origin, c2.origin);
    EXPECT_EQ(c1.radius, c2.radius);
    EXPECT_EQ(c1.layer, c2.layer);
    EXPECT_EQ(c1.can_collide_with, c2.can_collide_with);



}