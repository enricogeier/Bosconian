#include "SpaceStation.h"

SpaceStation::SpaceStation(Vector2 position, std::vector<CollisionCircle> collision_circles, Vector2 &scale, bool horizontal)
: GameObject(position, collision_circles[0], Type::SPACE_STATION, scale)
{
    if(horizontal)
    {
        for(int i = 0; i < 6; i++)
        {
            cannons[i] = Cannon(
                    Vector2(
                            position.x + (h_cannon_positions[i].x * scale.x),
                            position.y +  (h_cannon_positions[i].y * scale.y)
                            ),
                    i % 3 == 0 ? collision_circles[2] : collision_circles[1], scale
                            );
        }
    }
    else
    {
        for(int i = 0; i < 6; i++)
        {
            cannons[i] = Cannon(
                    Vector2(
                            position.x + (v_cannon_positions[i].x * scale.x),
                            position.y +  (v_cannon_positions[i].y * scale.y)
                    ),
                    i % 3 == 0 ? collision_circles[1] : collision_circles[4], scale
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
