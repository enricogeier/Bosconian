#include "SpaceStation.h"

SpaceStation::SpaceStation(Vector2 position, std::vector<CollisionCircle> collision_circles, Vector2 &scale, bool horizontal)
: GameObject(position, collision_circles[0], Type::SPACE_STATION, scale), horizontal(horizontal)
{
    if(horizontal)
    {
        CannonType cannon_types[] =
                {
                CannonType::N,
                CannonType::NE,
                CannonType::SE,
                CannonType::S,
                CannonType::SW,
                CannonType::NW,
                };

        for(int i = 0; i < 6; i++)
        {
            cannons[i] = Cannon(
                    Vector2(
                            position.x + (h_cannon_positions[i].x * scale.x),
                            position.y +  (h_cannon_positions[i].y * scale.y)
                            ),
                    Vector2(
                            h_shoot_positions_offset[i].x * scale.x,
                            h_shoot_positions_offset[i].y * scale.y
                            ),
                    cannon_types[i],
                    i % 3 == 0 ? collision_circles[2] : collision_circles[1],
                    i % 3 == 0 ? collision_circles[3] : collision_circles[1],
                    scale
                            );
        }
    }
    else
    {
        CannonType cannon_types[] =
                {
                        CannonType::W,
                        CannonType::NW,
                        CannonType::NE,
                        CannonType::E,
                        CannonType::SE,
                        CannonType::SW,
                };

        for(int i = 0; i < 6; i++)
        {
            cannons[i] = Cannon(
                    Vector2(
                            position.x + (v_cannon_positions[i].x * scale.x),
                            position.y +  (v_cannon_positions[i].y * scale.y)
                    ),
                    Vector2(
                            v_shoot_positions_offset[i].x * scale.x,
                            v_shoot_positions_offset[i].y * scale.y
                    ),
                    cannon_types[i],
                    i % 3 == 0 ? collision_circles[1] : collision_circles[4],
                    i % 3 == 0 ? collision_circles[5] : collision_circles[4],
                    scale
            );
        }
    }

}

void SpaceStation::update_cannon_positions(Vector2& offset)
{
    for(auto& cannon : cannons)
    {
        cannon.position = cannon.position + offset;
        cannon.collision_circle.origin = cannon.position + cannon.collision_circle.initial_origin;
    }

}


void SpaceStation::update_cannons()
{
    if(cannons[0].state == State::EXPLODE && !updated)
    {
        updated = true;

        if(horizontal)
        {
            h_cannon_new_position_offset.x *= cannons[0].scale.x;
            h_cannon_new_position_offset.y *= cannons[0].scale.y;

            cannons[0].update_position(h_cannon_new_position_offset);
        }
        else
        {
            v_cannon_new_position_offset.x *= cannons[0].scale.x;
            v_cannon_new_position_offset.y *= cannons[0].scale.y;
            
            cannons[0].update_position(v_cannon_new_position_offset);
        }

    }

}

int SpaceStation::get_amount_of_cannons()
{
    int amount = 0;

    for(Cannon& cannon : cannons)
    {
        ++amount;
    }

    return amount;

}