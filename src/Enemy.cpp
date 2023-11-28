#include "Enemy.h"



void Enemy::move(Vector2& move_direction, float &delta)
{
    if(collision_circle.layer == Layer::ENEMY)
    {

    }

    if(state == State::NORMAL)
    {

    }
    else
    {
        // TODO: play explosion


        state = State::DESTROY;

    }

    collision_circle.origin = collision_circle.position_in_sprite + position;

}
