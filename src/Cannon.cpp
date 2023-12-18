#include "Cannon.h"

void Cannon::check_state()
{
    if(state == State::EXPLODE)
    {
        state = State::DESTROY;

        collision_circle = explosion_circle;
        collision_circle.origin = collision_circle.initial_origin + position;

    }
}

void Cannon::update_position(Vector2 &offset)
{
    position += offset;
    collision_circle.origin = collision_circle.initial_origin + position;
}