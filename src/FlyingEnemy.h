#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include "Enemy.h"

class FlyingEnemy : public Enemy
{
public:

    explicit FlyingEnemy(Vector2 position) : Enemy(position)
    {
    }


    void move(Vector2& move_direction, float& delta);

};


#endif
