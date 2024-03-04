#include "Bullet.h"

void Bullet::increment(int &a)
{
    ++a;
}

void Bullet::move(float &delta)
{
    if(state == State::NORMAL)
    {
        position += direction.clamp() * (float)speed * delta;

        collision_circle.origin = collision_circle.initial_origin + position;
    }
}