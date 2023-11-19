#include "Bullet.h"

void Bullet::move(float &delta)
{
    if(state == State::NORMAL)
    {
        position += direction * (float)speed * delta;

        collision_circle.origin = collision_circle.position_in_sprite + position;
    }
}