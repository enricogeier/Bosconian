#include "../src/GameObject.h"
#include <gtest/gtest.h>

TEST(GameObject, constructor)
{
    GameObject g0 = GameObject(Vector2(), CollisionCircle(), Type::PLAYER);
    GameObject g1 = GameObject(Vector2(17.0f, 17.0f), CollisionCircle(), Type::CANNON );

    EXPECT_EQ(g0.id, 1);
    EXPECT_EQ(g1.id, 2);

    EXPECT_EQ(g0.position, Vector2());
    EXPECT_EQ(g1.position, Vector2(17.0f, 17.0f));
    EXPECT_EQ(g0.type, Type::PLAYER);
    EXPECT_EQ(g1.type, Type::CANNON);

    GameObject g3 = g0;

    EXPECT_TRUE(g3 == g0);

}

