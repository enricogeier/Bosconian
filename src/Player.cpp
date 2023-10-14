#include "Player.h"

Player::Player(Vector2 position,
               Vector2 direction,
               int lives,
               float max_velocity,
               float min_velocity) : position(position), direction(direction), lives(lives), max_velocity(max_velocity), min_velocity(min_velocity)
{
}

void Player::move(Vector2& new_direction, float& delta)
{

    if(new_direction != this->direction && new_direction != Vector2())
    {
        this->direction = new_direction;
    }

    this->clamped_direction = this->direction.clamp();

    Vector2 new_position = Vector2(position.x + (clamped_direction.x * max_velocity * delta), position.y + (clamped_direction.y * max_velocity * delta));
    this->position = new_position;


}
