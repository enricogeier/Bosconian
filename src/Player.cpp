#include "Player.h"

Player::Player(Vector2 direction) : direction(direction)
{
    position = START_POSITION;
}

void Player::move(Vector2& new_direction, float& delta)
{

    if(new_direction != this->direction && new_direction != Vector2())
    {
        this->direction = new_direction;
    }

    this->clamped_direction = this->direction.clamp();

    Vector2 new_position = Vector2(position.x + (clamped_direction.x * MAX_VELOCITY * delta), position.y + (clamped_direction.y * MAX_VELOCITY * delta));
    this->position = new_position;


}
