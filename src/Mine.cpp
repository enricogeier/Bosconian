#include "Mine.h"


void Mine::explode()
{
    auto current_time_point = std::chrono::high_resolution_clock::now();
    explosion_start = std::chrono::duration_cast<std::chrono::microseconds>(current_time_point.time_since_epoch());

    collision_circle.initial_origin = position;
    collision_circle.radius *= 1.5;

    position.x -= 8 * scale.x;
    position.y -= 8 * scale.y;




}


bool Mine::check_explosion()
{
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto current_time = std::chrono::duration_cast<std::chrono::microseconds>(current_time_point.time_since_epoch());

    if(std::chrono::duration_cast<std::chrono::microseconds>(current_time - explosion_start) > explosion_duration)
    {
        return true;
    }
    else
    {
        return false;
    }
}

