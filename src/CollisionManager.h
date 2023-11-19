#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "CollisionCircle.h"
#include "SpriteSheet.h"


class CollisionManager
{
private:
    static std::vector<CollisionCircle> collision_circles;

public:

    static Vector2 scale;

    static void create_collision_circles();

    static CollisionCircle get_player_collision();

    static CollisionCircle get_e_type_collision();

    static CollisionCircle get_i_type_collision();

    static CollisionCircle get_p_type_collision();

    static CollisionCircle get_spy_collision();

    static CollisionCircle get_mine_collision();

    static CollisionCircle get_asteroid_collision();

    static CollisionCircle get_mine_explosion_collision();

    static CollisionCircle get_player_bullet_collision();

    static CollisionCircle get_enemy_bullet_collision();

};


#endif