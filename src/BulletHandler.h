#ifndef BULLETHANDLER_H
#define BULLETHANDLER_H

#include <list>
#include "Vector2.h"
#include "Bullet.h"
#include "QuadTree.h"
#include "Score.h"
#include "CollisionManager.h"
#include "Player.h"

class BulletHandler
{
private:
    std::list<Bullet> player_bullet_list;
    std::list<Bullet> enemy_bullet_list;
    const float BORDER = 700.0f;

public:
    float previous_player_speed = 0.0f;

    BulletHandler() = default;

    void insert_player_bullets(Player& player, CollisionManager& collision_manager);

    void insert_enemy_bullet(Vector2& position, Vector2& direction, CollisionManager& collision_manager);

    [[nodiscard]] std::list<Bullet> get_player_bullets() const;
    std::list<Bullet> get_enemy_bullets() const;

    void check_collisions(QuadTree& quad_tree, Score& score);

    void clear_bullets();

    void move_bullets(Player& player, QuadTree& quad_tree, float& delta);

};


#endif
