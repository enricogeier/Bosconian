#include "../src/BulletHandler.h"
#include <gtest/gtest.h>

float epsilon = 0.001f;

TEST(BulletHandler, insertPlayerBullets)
{
    BulletHandler instance = BulletHandler();

    CollisionManager collisionManager;

    Player p0, p1, p2, p3, p4, p5, p6, p7;

    p0.direction = Vector2(1.0f);
    p1.direction = Vector2(-1.0f);
    p2.direction = Vector2(0.0f, -1.0f);
    p3.direction = Vector2(1.0f, -1.0f);
    p4.direction = Vector2(1.0f, 0.0f);
    p5.direction = Vector2(0.0f, 1.0f);
    p6.direction = Vector2(-1.0f, 1.0f);
    p7.direction = Vector2(-1.0f, 0.0f);

    p0.clamped_direction = p0.direction.clamp();
    p1.clamped_direction = p1.direction.clamp();
    p2.clamped_direction = p2.direction.clamp();
    p3.clamped_direction = p3.direction.clamp();
    p4.clamped_direction = p4.direction.clamp();
    p5.clamped_direction = p5.direction.clamp();
    p6.clamped_direction = p6.direction.clamp();
    p7.clamped_direction = p7.direction.clamp();


    instance.insert_player_bullets(p0, collisionManager);

    std::list<Bullet> result = instance.get_bullets();

    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p0.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p0.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p0.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p0.clamped_direction.y) < epsilon);
    EXPECT_EQ(result.front().speed * 2, result.back().speed);
    result.clear();
    instance.clear_bullets();


    instance.insert_player_bullets(p1, collisionManager);
    result = instance.get_bullets();
    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p1.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p1.clamped_direction.y) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p1.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p1.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_EQ(result.front().speed, result.back().speed * 2);
    result.clear();
    instance.clear_bullets();

    instance.insert_player_bullets(p2, collisionManager);
    result = instance.get_bullets();
    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p2.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p2.clamped_direction.y) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p2.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p2.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_EQ(result.front().speed, result.back().speed * 2);
    result.clear();
    instance.clear_bullets();

    instance.insert_player_bullets(p3, collisionManager);
    result = instance.get_bullets();
    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p3.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p3.clamped_direction.y) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p3.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p3.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_EQ(result.front().speed, result.back().speed * 2);
    result.clear();
    instance.clear_bullets();

    instance.insert_player_bullets(p4, collisionManager);
    result = instance.get_bullets();
    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p4.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p4.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p4.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p4.clamped_direction.y) < epsilon);
    EXPECT_EQ(result.front().speed * 2, result.back().speed);
    result.clear();
    instance.clear_bullets();

    instance.insert_player_bullets(p5, collisionManager);
    result = instance.get_bullets();
    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p5.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p5.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p5.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p5.clamped_direction.y) < epsilon);
    EXPECT_EQ(result.front().speed * 2, result.back().speed);
    result.clear();
    instance.clear_bullets();

    instance.insert_player_bullets(p6, collisionManager);
    result = instance.get_bullets();
    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p6.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p6.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p6.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p6.clamped_direction.y) < epsilon);
    EXPECT_EQ(result.front().speed * 2, result.back().speed);
    result.clear();
    instance.clear_bullets();

    instance.insert_player_bullets(p7, collisionManager);
    result = instance.get_bullets();
    EXPECT_TRUE(std::abs(result.front().clamped_direction.x - p7.clamped_direction.x) < epsilon);
    EXPECT_TRUE(std::abs(result.front().clamped_direction.y - p7.clamped_direction.y) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.x - p7.clamped_direction.x * (-1.0f)) < epsilon);
    EXPECT_TRUE(std::abs(result.back().clamped_direction.y - p7.clamped_direction.y * (-1.0f)) < epsilon);
    EXPECT_EQ(result.front().speed, result.back().speed * 2);
    result.clear();
    instance.clear_bullets();



}

TEST(BulletHandler, insertEnemyBullet)
{
    BulletHandler instance = BulletHandler();
    CollisionManager collisionManager;

    Vector2 value = Vector2(17.0f, 17.0f);
    instance.insert_enemy_bullet(value, value, collisionManager);

    Bullet bullet = instance.get_bullets().front();

    EXPECT_EQ(bullet.position, value);
    EXPECT_EQ(bullet.direction, Vector2(1.0f, 1.0f));
    EXPECT_EQ(bullet.speed, 250);

}



TEST(BulletHandler, moveBullets)
{
    BulletHandler instance = BulletHandler();
    CollisionManager collisionManager;
    Player player = Player();
    player.direction = Vector2(-1.0f, 0.0f);
    player.clamped_direction = player.direction.clamp();
    QuadTree quadTree = QuadTree();
    float delta = 0.09f;

    instance.insert_player_bullets(player, collisionManager);

    float previousYFront = 0.0f;
    float previousYBack = 0.0f;

    for(int i = 0; i < 99; i++)
    {
        instance.move_bullets(player, quadTree, delta);
        std::list<Bullet> result = instance.get_bullets();

        if(result.size() >= 2)
        {
            float absFront = std::abs(result.front().position.x);
            float absBack = std::abs(result.back().position.x);

            EXPECT_TRUE(absFront > previousYFront);
            EXPECT_TRUE(absBack > previousYBack);

            previousYFront = absFront;
            previousYBack = absBack;
        }
        else if(result.size() == 1)
        {
            float absBack = std::abs(result.back().position.x);

            EXPECT_TRUE(absBack > previousYBack);

            previousYBack = absBack;
        }
        else
        {
            break;
        }



    }

    std::list<Bullet> result = instance.get_bullets();

    EXPECT_EQ(instance.get_bullets().size(), 0);

}