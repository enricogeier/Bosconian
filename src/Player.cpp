#include "Player.h"

const Vector2 Player::START_POSITION = Vector2();
const float Player::MAX_VELOCITY = 300;
const float Player::MIN_VELOCITY = 200;
const float Player::ACCELERATION = 1.005;

void Player::move(Vector2& new_direction, float& delta, bool& accelerate)
{
    if(state == State::NORMAL)
    {

        if(new_direction != this->direction && new_direction != Vector2())
        {
            this->direction = new_direction;
        }

        this->clamped_direction = this->direction.clamp();

        if(accelerate || do_acceleration)
        {
            if(current_velocity >= MAX_VELOCITY)
            {
                do_acceleration = false;
                current_velocity = MAX_VELOCITY;
            }
            else
            {
                do_acceleration = true;
                current_velocity *= ACCELERATION;
            }
        }


        Vector2 new_position = Vector2(
                position.x + (clamped_direction.x * current_velocity * delta),
                position.y + (clamped_direction.y * current_velocity * delta)
                );

        position = new_position;


        collision_circle.origin = collision_circle.initial_origin + position;
    }

}
