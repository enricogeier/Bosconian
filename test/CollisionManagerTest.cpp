#include "../src/BulletHandler.h"
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


}

TEST(CollisionManager, iTypeCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}

TEST(CollisionManager, pTypeCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}
TEST(CollisionManager, spyCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}
TEST(CollisionManager, mineCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}
TEST(CollisionManager, asteroidCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}
TEST(CollisionManager, mineExplosionCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}
TEST(CollisionManager, playerBulletCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}
TEST(CollisionManager, enemyBulletCollision)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}
TEST(CollisionManager, spaceStationCollisions)
{
    CollisionManager collisionManager;
    collisionManager.create_collision_circles();


}