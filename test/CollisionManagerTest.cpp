#include "../src/CollisionManager.h"
#include <gtest/gtest.h>

TEST(CollisionManager, playerCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_player_collision();

    EXPECT_EQ(circle.origin, Vector2(7 * collisionManager.scale.x, 8 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 7.0f);
    EXPECT_EQ(circle.layer, Layer::PLAYER);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);


}

TEST(CollisionManager, eTypeCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_e_type_collision();

    EXPECT_EQ(circle.origin, Vector2(7 * collisionManager.scale.x, 7 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 10.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);

}

TEST(CollisionManager, iTypeCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_i_type_collision();

    EXPECT_EQ(circle.origin, Vector2(8 * collisionManager.scale.x, 8 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 12.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);


}

TEST(CollisionManager, pTypeCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_p_type_collision();

    EXPECT_EQ(circle.origin, Vector2(7 * collisionManager.scale.x, 8 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 12.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);


}
TEST(CollisionManager, spyCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_spy_collision();

    EXPECT_EQ(circle.origin, Vector2(7 * collisionManager.scale.x, 8 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 12.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);


}
TEST(CollisionManager, mineCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_mine_collision();

    EXPECT_EQ(circle.origin, Vector2(7 * collisionManager.scale.x, 7 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 12.0f);
    EXPECT_EQ(circle.layer, Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);


}
TEST(CollisionManager, asteroidCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_asteroid_collision();

    EXPECT_EQ(circle.origin, Vector2(7 * collisionManager.scale.x, 6 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 12.0f);
    EXPECT_EQ(circle.layer, Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);


}
TEST(CollisionManager, mineExplosionCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_mine_explosion_collision();

    EXPECT_EQ(circle.origin, Vector2(7 * collisionManager.scale.x, 8 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 8.0f);
    EXPECT_EQ(circle.layer, Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::ENEMY_BULLET);


}
TEST(CollisionManager, playerBulletCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_player_bullet_collision();

    EXPECT_EQ(circle.origin, Vector2(6 * collisionManager.scale.x, 7 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 4.0f);
    EXPECT_EQ(circle.layer, Layer::PLAYER_BULLET);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::CELESTIAL_OBJECT);


}
TEST(CollisionManager, enemyBulletCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_enemy_bullet_collision();

    EXPECT_EQ(circle.origin, Vector2(6 * collisionManager.scale.x, 7 * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 4.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY_BULLET);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::PLAYER);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::CELESTIAL_OBJECT);


}
TEST(CollisionManager, spaceStationCollisions)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_space_station_collisions()[0];

    EXPECT_EQ(circle.origin, Vector2(16.0f * collisionManager.scale.x, 11.0f * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 8.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::PLAYER_BULLET);

}

TEST(CollisionManager, square)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_space_station_collisions()[1];

    EXPECT_EQ(circle.origin, Vector2(6.0f * collisionManager.scale.x, 7.0f * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 7.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::PLAYER_BULLET);

}

TEST(CollisionManager, h1)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_space_station_collisions()[2];

    EXPECT_EQ(circle.origin, Vector2(16.0f * collisionManager.scale.x, 11.0f * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 16.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::PLAYER_BULLET);
}

TEST(CollisionManager, h2)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_space_station_collisions()[3];

    EXPECT_EQ(circle.origin, Vector2(16.0f * collisionManager.scale.x, 7.0f * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 10.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::PLAYER_BULLET);
}

TEST(CollisionManager, v1)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_space_station_collisions()[4];

    EXPECT_EQ(circle.origin, Vector2(12.0f * collisionManager.scale.x, 11.0f * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 8.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::PLAYER_BULLET);
}

TEST(CollisionManager, v2)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();

    CollisionCircle circle = collisionManager.get_space_station_collisions()[5];

    EXPECT_EQ(circle.origin, Vector2(4.0f * collisionManager.scale.x, 7.0f * collisionManager.scale.y));
    EXPECT_EQ(circle.radius, collisionManager.scale.x * 6.0f);
    EXPECT_EQ(circle.layer, Layer::ENEMY);
    EXPECT_EQ(circle.can_collide_with.front(), Layer::CELESTIAL_OBJECT);
    EXPECT_EQ(circle.can_collide_with.back(), Layer::PLAYER_BULLET);
}