#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <list>
#include "Vector2.h"
#include "Bullet.h"
#include "QuadTree.h"

class BulletHandler
{
private:
    std::list<Bullet> bullet_list;

public:
    BulletHandler() = default;

    void insert_player_bullets(Vector2& player_position, Vector2& player_direction, Vector2& player_clamped_direction,
                               CollisionCircle collision_circle);

    std::list<Bullet>& get_bullets();

    void check_collisions(QuadTree& quad_tree);

    void move_player_bullet(Vector2& position, Vector2& clamped_direction, QuadTree& quad_tree, float& delta);


};


#endif
