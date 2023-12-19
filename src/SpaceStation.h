#ifndef SPACESTATION_H
#define SPACESTATION_H

#include <utility>
#include "Cannon.h"


class SpaceStation : public GameObject
{
private:
    bool updated = false;

    Vector2 v_cannon_positions[6] = {
            Vector2(-16.0f, 0.0f),
            Vector2(-8.0f, -24.0f),
            Vector2(24.0f, -24.0f),
            Vector2(40.0f, 0.0f),
            Vector2(24.0f, 16.0f),
            Vector2(-8.0f, 16.0f),
    };

    Vector2 h_cannon_positions[6] = {
            Vector2(0.0f, -24.0f),
            Vector2(32.0f, -8.0f),
            Vector2(32.0f, 16.0f),
            Vector2(0.0f, 24.0f),
            Vector2(-16.0f, 16.0f),
            Vector2(-16.0f, -8.0f),
    };

    Vector2 v_cannon_new_position_offset = Vector2(8.0f, 0.0f);
    Vector2 h_cannon_new_position_offset = Vector2(0.0f, 8.0f);

public:

    Cannon cannons[6];
    bool horizontal = false;

    explicit SpaceStation(Vector2 position, std::vector<CollisionCircle> collision_circles, Vector2& scale, bool horizontal = false);

    void update_cannon_positions(Vector2& offset);

    void update_cannons();

    int get_amount_of_cannons();

};



#endif
