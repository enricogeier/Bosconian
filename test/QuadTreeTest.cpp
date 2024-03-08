#include "../src/QuadTree.h"
#include "../src/Enemy.h"
#include "../src/CollisionManager.h"
#include <gtest/gtest.h>

TEST(QuadTree, checkCollision)
{
    QuadTree quadTree = QuadTree({0, 0, 4500, 7800});
    CollisionManager collisionManager;
    Sound sound;
    Score score = Score(&sound);


    std::list<Enemy> enemies = {

            Enemy(Vector2(2000.0f, 3200.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(2677.0f, 4800.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(2000.0f, 5000.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(1677.0f, 4800.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),

            Enemy(Vector2(500.0f, 500.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(504.0f, 504.0f), collisionManager.get_mine_collision(), Type::MINE),
            Enemy(Vector2(2000.0f, 2000.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(2004.0f, 2004.0f), collisionManager.get_mine_collision(), Type::MINE),
            Enemy(Vector2(4000.0f, 2000.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(4004.0f, 2004.0f), collisionManager.get_mine_collision(), Type::MINE),
            Enemy(Vector2(3900.0f, 4000.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(3904.0f, 4004.0f), collisionManager.get_mine_collision(), Type::MINE),
            Enemy(Vector2(5500.0f, 7500.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(5504.0f, 7504.0f), collisionManager.get_mine_collision(), Type::MINE),
            Enemy(Vector2(2000.0f, 7500.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(2004.0f, 7504.0f), collisionManager.get_mine_collision(), Type::MINE),
            Enemy(Vector2(3900.0f, 7500.0f), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(3904.0f, 7504.0f), collisionManager.get_mine_collision(), Type::MINE),

            Enemy(Vector2(1500, 2600), collisionManager.get_i_type_collision(), Type::I_TYPE),
            Enemy(Vector2(1498, 2598), collisionManager.get_mine_collision(), Type::MINE),

    };

    for(auto& enemy: enemies)
    {
        quadTree.insert(enemy);
    }

    for(auto& enemy : enemies)
    {
        quadTree.check_collision(enemy, score);
    }

    EXPECT_EQ(score.score, 490);

}
