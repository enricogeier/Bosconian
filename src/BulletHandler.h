#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <list>
#include "Vector2.h"
#include "Bullet.h"
#include "QuadTree.h"
#include "CollisionManager.h"
#include "Player.h"

class BulletHandler
{
private:
    std::list<Bullet> bullet_list;

public:
    float previous_player_speed = 0.0f;

    BulletHandler() = default;

    void insert_player_bullets(Player& player, CollisionManager& collision_manager);

    std::list<Bullet>& get_bullets();

    void check_collisions(QuadTree& quad_tree);

    void move_player_bullet(Player& player, QuadTree& quad_tree, float& delta);


};


#endif
