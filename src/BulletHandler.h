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
    BulletHandler() = default;

    void insert_player_bullets(Player& player, CollisionManager& collision_manager);

    std::list<Bullet>& get_bullets();

    void check_collisions(QuadTree& quad_tree);

    void move_player_bullet(Vector2& position, Vector2& clamped_direction, QuadTree& quad_tree, float& delta);


};


#endif
