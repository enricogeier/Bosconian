#include "Player.h"

const Vector2 Player::START_POSITION = Vector2(0, 0);
const float Player::MAX_VELOCITY = 300.0f; // default: 300
const float Player::MIN_VELOCITY = 100.0f;


void Player::move(Vector2& new_direction, float& delta)
{
    if(state == State::NORMAL)
    {

        if(new_direction != this->direction && new_direction != Vector2())
        {
            this->direction = new_direction;
        }

        this->clamped_direction = this->direction.clamp();

        Vector2 new_position = Vector2(position.x + (clamped_direction.x * MAX_VELOCITY * delta), position.y + (clamped_direction.y * MAX_VELOCITY * delta));
        position = new_position;


        collision_circle.origin = position + Vector2(normal_sprites.back().w / 2, normal_sprites.back().h / 2);

    }
    else
    {
        // TODO: implement player explosion
        // for testing
        state = State::NORMAL;
        move(new_direction, delta);
    }


}
