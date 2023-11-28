#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "CollisionCircle.h"



class CollisionManager
{
private:
    std::vector<CollisionCircle> collision_circles;

public:

    explicit CollisionManager(Vector2 scale = Vector2(1.0f, 1.0f));

    Vector2 scale = Vector2(1.0f, 1.0f);

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

};


#endif