#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
    create_collision_circles();
}


void CollisionManager::create_collision_circles()
{

    collision_circles = { CollisionCircle  // player
                                  {Vector2(7 * scale.x, 8 * scale.y),
                                   7.0f * scale.x,
                                    Layer::PLAYER,
                                   std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::ENEMY, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // e type
                                  {
                                          Vector2(7 * scale.x, 7 * scale.y),
                                          10.0f * scale.x,
                                          Layer::ENEMY,
                                          std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // i type
                                  {
                                          Vector2(8 * scale.x, 8 * scale.y),
                                          12.0f * scale.x,
                                          Layer::ENEMY,
                                          std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // p type
                                  {
                                          Vector2(7 * scale.x, 8 * scale.y),
                                          12.0f * scale.x,
                                          Layer::ENEMY,
                                          std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // spy
                                  {
                                          Vector2(7 * scale.x, 8 * scale.y),
                                          12.0f * scale.x,
                                          Layer::ENEMY,
                                          std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // mine
                                  {
                                          Vector2(7.0f * scale.x, 7.0f * scale.y),
                                          12.0f * scale.x,
                                          Layer::CELESTIAL_OBJECT,
                                          std::list<Layer>{Layer::ENEMY, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // asteroid
                                  {
                                          Vector2(7.0f * scale.x, 6.0f * scale.y),
                                          12.0f * scale.x,
                                          Layer::CELESTIAL_OBJECT,
                                          std::list<Layer>{Layer::ENEMY, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // mine explosion
                                  {
                                          Vector2(7.0f * scale.x, 8.0f * scale.y),
                                          8.0f * scale.x,
                                          Layer::CELESTIAL_OBJECT,
                                          std::list<Layer>{Layer::ENEMY, Layer::PLAYER, Layer::PLAYER_BULLET, Layer::ENEMY_BULLET}
                                  },
                          CollisionCircle // player bullet
                                  {
                                          Vector2(6.0f * scale.x, 7.0f * scale.y),
                                          4.0f * scale.x,
                                          Layer::PLAYER_BULLET,
                                          std::list<Layer>{Layer::ENEMY, Layer::CELESTIAL_OBJECT}
                                  },

                          CollisionCircle // enemy bullet
                                  {
                                          Vector2(6.0f * scale.x, 7.0f * scale.y),
                                          4.0f * scale.x,
                                          Layer::ENEMY_BULLET,
                                          std::list<Layer>{Layer::PLAYER, Layer::CELESTIAL_OBJECT}
                                  },
                          CollisionCircle // space station
                                  {
                                    Vector2(16.0f * scale.x, 11.0f * scale.y),
                                    8.0f * scale.x,
                                    Layer::ENEMY,
                                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET}
                                  },
                          CollisionCircle // cannon (square)
                                  {
                                    Vector2(6.0f * scale.x, 7.0f * scale.y),
                                    7.0f * scale.x,
                                    Layer::ENEMY,
                                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET}
                                  },
                          CollisionCircle // cannon h1
                                  {
                                    Vector2(16.0f * scale.x, 11.0f * scale.y),
                                    16.0f * scale.x,
                                    Layer::ENEMY,
                                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET}
                                  },
                          CollisionCircle // cannon h2
                                  {
                                    Vector2(16.0f * scale.x, 7.0f * scale.y),
                                    10.0f * scale.x,
                                    Layer::ENEMY,
                                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET}
                                  },
                          CollisionCircle // cannon v1
                                  {
                                    Vector2(12.0f * scale.x, 11.0f * scale.y),
                                    8.0f * scale.x,
                                    Layer::ENEMY,
                                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET}
                                  },
                          CollisionCircle // cannon v2
                                  {
                                    Vector2(4.0f * scale.x, 7.0f * scale.y),
                                    6.0f * scale.x,
                                    Layer::ENEMY,
                                    std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::PLAYER, Layer::PLAYER_BULLET}
                                  }


                                  };
}



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

std::vector<CollisionCircle> CollisionManager::get_space_station_collisions()
{
    return std::vector<CollisionCircle>
    {
            collision_circles[10],
            collision_circles[11],
            collision_circles[12],
            collision_circles[13],
            collision_circles[14],
            collision_circles[15],

            };
}

