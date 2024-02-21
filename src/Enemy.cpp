#include "Enemy.h"



void Enemy::move(Vector2& player_position, float &delta)
{

    direction = player_position - position;
    clamped_direction = direction.clamp();

    if(clamped_direction.x < 0)
    {
        float difference = 1.0f;
        float previous_value = 0.0f;
        for(auto& value : VALUE_LESS_THAN_0)
        {
            float current_difference = clamped_direction.x - value;
            if(std::abs(current_difference) < std::abs(difference))
            {
                difference = current_difference;
                previous_value = value;
                direction.x = previous_value;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        float difference = 1.0f;
        float previous_value = 0.0f;
        for(auto& value : VALUE_0_OR_HIGHER)
        {
            float current_difference = clamped_direction.x - value;
            if(std::abs(current_difference) < std::abs(difference))
            {
                difference = current_difference;
                previous_value = value;
                direction.x = previous_value;
            }
            else
            {
                break;
            }
        }
    }

    if(direction.x == 1.0f || direction.x == -1.0f)
    {
        if(clamped_direction.y < 0)
        {
            float difference = 1.0f;
            float previous_value = 0.0f;
            for(auto& value : VALUE_LESS_THAN_0)
            {
                float current_difference = clamped_direction.y - value;
                if(std::abs(current_difference) < std::abs(difference))
                {
                    difference = current_difference;
                    previous_value = value;
                    direction.y = previous_value;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            float difference = 1.0f;
            float previous_value = 0.0f;
            for(auto& value : VALUE_0_OR_HIGHER)
            {
                float current_difference = clamped_direction.y - value;
                if(std::abs(current_difference) < std::abs(difference))
                {
                    difference = current_difference;
                    previous_value = value;
                    direction.y = previous_value;
                }
                else
                {
                    break;
                }
            }
        }
    }
    else
    {
        if(clamped_direction.y < 0.0f)
        {
            direction.y = -1.0f;
        }
        else
        {
            direction.y = 1.0f;
        }
    }




    clamped_direction = direction.clamp();


    Vector2 new_position = Vector2(
            position.x + (clamped_direction.x * VELOCITY * delta),
            position.y + (clamped_direction.y * VELOCITY * delta)
    );

    position = new_position;

    collision_circle.origin = collision_circle.initial_origin + position;

}
