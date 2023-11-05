#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include "Enemy.h"


class FlyingEnemy : public Enemy
{
private:
    bool leader_of_formation = false;
public:

    explicit FlyingEnemy(Vector2 position, std::vector<Rectangle> player_sprite, std::vector<Rectangle> explosion_sprite)
    : Enemy(position, std::move(player_sprite), std::move(explosion_sprite))
    {
    }


    void move(Vector2& move_direction, float& delta);

};


#endif
