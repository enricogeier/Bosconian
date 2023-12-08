#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "CollisionCircle.h"



class CollisionManager
{
private:
    std::vector<CollisionCircle> collision_circles;

public:

    Vector2 scale = Vector2(4.0f, 4.0f);

    explicit CollisionManager();

    void create_collision_circles();

    CollisionCircle get_player_collision();

    CollisionCircle get_e_type_collision();

    CollisionCircle get_i_type_collision();

    CollisionCircle get_p_type_collision();

    CollisionCircle get_spy_collision();

    CollisionCircle get_mine_collision();

    CollisionCircle get_asteroid_collision();

    CollisionCircle get_mine_explosion_collision();

    CollisionCircle get_player_bullet_collision();

    CollisionCircle get_enemy_bullet_collision();

    std::vector<CollisionCircle> get_space_station_collisions();

};


#endif