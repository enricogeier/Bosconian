#include "CollisionManager.h"

const std::vector<CollisionCircle> CollisionManager::collision_circles{
    //TODO: implement Collision Circles

    CollisionCircle  // player
    {Vector2(),
     2.0f,
     Layer::PLAYER,
     std::list<Layer>{Layer::CELESTIAL_OBJECT, Layer::ENEMY, Layer::ENEMY_BULLET}
     },







};

// TODO: implement functions correctly

CollisionCircle CollisionManager::get_player_collision()
{
    return collision_circles[0];
}

CollisionCircle CollisionManager::get_e_type_collision()
{
    return collision_circles[0];
}

CollisionCircle CollisionManager::get_i_type_collision()
{

}

CollisionCircle CollisionManager::get_p_type_collision()
{

}

CollisionCircle CollisionManager::get_spy_collision()
{

}

CollisionCircle CollisionManager::get_mine_collision()
{

}

CollisionCircle CollisionManager::get_asteroid_collision()
{

}

CollisionCircle CollisionManager::get_mine_explosion_collision()
{

}

CollisionCircle CollisionManager::get_bullet_collision()
{
    return collision_circles[0];
}
