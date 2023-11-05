#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject
{
public:

    explicit Enemy(Vector2 position, std::vector<Rectangle> player_sprite, std::vector<Rectangle> explosion_sprite) :
    GameObject(position, std::move(player_sprite), std::move(explosion_sprite))
    {
    }

    void shoot(Vector2& shoot_direction);
};

#endif
