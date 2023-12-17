#include "Cannon.h"

void Cannon::check_state()
{
    if(state == State::EXPLODE && !exploded)
    {
        exploded = true;
        collision_circle = explosion_circle;
    }
}

void Cannon::update_position(Vector2 &new_position)
{
    position = new_position;
    collision_circle.origin = collision_circle.initial_origin + position;
}