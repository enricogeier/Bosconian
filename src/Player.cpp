#include "Player.h"

Player::Player(Vector2 position,
               Vector2 direction,
               int lives,
               float max_velocity,
               float min_velocity) : position(position), direction(direction), lives(lives), max_velocity(max_velocity), min_velocity(min_velocity)
{
}

void Player::move(Vector2& new_direction)
{

    if(new_direction != this->direction && new_direction != Vector2())
    {
        this->direction = new_direction.clamp();

    }


    Vector2 new_position = Vector2(position.x + (direction.x * max_velocity), position.y + (direction.y * max_velocity));
    this->position = new_position;


}
