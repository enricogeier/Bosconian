#include "CollisionManager.h"

const std::vector<CollisionCircle> CollisionManager::collision_circles{
    //TODO: implement Collision Circles

    CollisionCircle  // player
    {Vector2(),
     20.0f,
     Layer::PLAYER,
     std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::ENEMY, Layer::ENEMY_BULLET}
     },
     CollisionCircle // e type
     {
        Vector2(),
        20.0f,
        Layer::ENEMY,
        std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
     },
    CollisionCircle // i type
            {
                    Vector2(),
                    20.0f,
                    Layer::ENEMY,
                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
            },
    CollisionCircle // p type
            {
                    Vector2(),
                    20.0f,
                    Layer::ENEMY,
                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
            },
    CollisionCircle // spy
            {
                    Vector2(),
                    20.0f,
                    Layer::ENEMY,
                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
            },
    CollisionCircle // mine
            {
                    Vector2(),
                    20.0f,
                    Layer::CELESTIAL_OBJECT,
                    std::list<Layer>{Layer::ENEMY, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
            },
    CollisionCircle // asteroid
            {
                    Vector2(),
                    20.0f,
                    Layer::CELESTIAL_OBJECT,
                    std::list<Layer>{Layer::ENEMY, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
            },
    CollisionCircle // mine explosion
            {
                    Vector2(),
                    20.0f,
                    Layer::CELESTIAL_OBJECT,
                    std::list<Layer>{Layer::ENEMY, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
            },
    CollisionCircle // player bullet
            {
                    Vector2(),
                    20.0f,
                    Layer::PLAYER_BULLET,
                    std::list<Layer>{Layer::ENEMY, Layer::CELESTIAL_OBJECT}
            },

    CollisionCircle // enemy bullet
            {
                    Vector2(),
                    20.0f,
                    Layer::ENEMY_BULLET,
                    std::list<Layer>{Layer::PLAYER, Layer::CELESTIAL_OBJECT}
            },



};


CollisionCircle CollisionManager::get_player_collision()
{
    return collision_circles[0];
}

CollisionCircle CollisionManager::get_e_type_collision()
{
    return collision_circles[1];
}

CollisionCircle CollisionManager::get_i_type_collision()
{
    return collision_circles[2];
}

CollisionCircle CollisionManager::get_p_type_collision()
{
    return collision_circles[3];
}

CollisionCircle CollisionManager::get_spy_collision()
{
    return collision_circles[4];
}

CollisionCircle CollisionManager::get_mine_collision()
{
    return collision_circles[5];
}

CollisionCircle CollisionManager::get_asteroid_collision()
{
    return collision_circles[6];
}

CollisionCircle CollisionManager::get_mine_explosion_collision()
{
    return collision_circles[7];
}

CollisionCircle CollisionManager::get_player_bullet_collision()
{
    return collision_circles[8];
}

CollisionCircle CollisionManager::get_enemy_bullet_collision()
{
    return collision_circles[9];
}

