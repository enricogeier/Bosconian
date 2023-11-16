#include "Enemy.h"



void Enemy::move(Vector2& move_direction, float &delta)
{
    if(state == State::NORMAL)
    {

    }


    collision_circle.origin = position + Vector2(normal_sprites.back().w * collision_circle.scale.x / 2, normal_sprites.back().h * collision_circle.scale.y / 2);
}