#ifndef SPACESTATION_H
#define SPACESTATION_H

#include <utility>
#include "Cannon.h"

class SpaceStation : public GameObject
{
private:
    bool updated = false;

    Vector2 v_shoot_positions_offset[6] = {
            Vector2(0.0f, 8.0f),
            Vector2(16.0f, 0.0f),
            Vector2(8.0f, 0.0f),
            Vector2(16.0f, 8.0f),
            Vector2(8.0f, 24.0f),
            Vector2(16.0f, 24.0f),
    };

    Vector2 h_shoot_positions_offset[6] = {
            Vector2(16.0f, 0.0f),
            Vector2(16.0f, 8.0f),
            Vector2(16.0f, 8.0f),
            Vector2(16.0f, 24.0f),
            Vector2(0.0f, 8.0f),
            Vector2(0.0f, 8.0f),
    };

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

    /**
     * Constructs a new SpaceStation object and its cannons.
     *
     * @param position The position of the SpaceStation in the game.
     * @param collision_circles  used for collision calculation.
     * @param scale used for collision calculation.
     * @param horizontal true if the SpaceStation is horizontal, false otherwise.
     */
    explicit SpaceStation(Vector2 position, std::vector<CollisionCircle> collision_circles, Vector2& scale, bool horizontal = false);

    /**
     * Updates cannon positions. Called when tile position has been changed.
     * @param offset Offset position used for change the cannon positions.
     */
    void update_cannon_positions(Vector2& offset);

    /**
     * Checks if cannons have been destroyed and possibly updates the cannons.
     */
    void update_cannons();

    /**
     * Retrieves amount of cannons which have not been destroyed yet.
     * @return amount of cannons which have not been destroyed yet.
     */
    int get_amount_of_cannons();

};



#endif
