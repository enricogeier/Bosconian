#include "Bullet.h"

void Bullet::move(float &delta)
{
    if(state == State::NORMAL)
    {
        position += direction * (float)speed * delta;

        collision_circle.origin = position + Vector2(normal_sprites.back().w  * collision_circle.scale.x / 2, normal_sprites.back().h * collision_circle.scale.y / 2);
    }
}