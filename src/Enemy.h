#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

class Enemy : public GameObject
{
public:

    explicit Enemy(Vector2 position) : GameObject(position)
    {
    }

    void shoot(Vector2& shoot_direction);
};

#endif
