#include "Enemy.h"



void Enemy::move(Vector2& move_direction, float &delta)
{
    if(state == State::NORMAL)
    {

    }
    else
    {
        // TODO: undo this
        state == State::NORMAL;
    }

    collision_circle.origin = collision_circle.position_in_sprite + position;

}