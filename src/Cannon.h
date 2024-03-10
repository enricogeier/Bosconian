#ifndef CANNON_H
#define CANNON_H

#include <utility>
#include <vector>
#include "GameObject.h"

enum CannonType
{
    N, NE, E, SE, S, SW, W, NW
};


class Cannon : public GameObject
{
private:
    CollisionCircle explosion_circle;



public:

    CannonType type = CannonType::N;
    Vector2 shoot_position_offset = Vector2();

    /**
     * Constructs a new Cannon object.
     *
     * @param position The position of the cannon. The position value for the Cannon instance
     * @param shoot_position_offset start position of a shoot
     * @param cannon_type Type of Cannon. See enum CannonType
     * @param collision_circle used for collision calculation. Default value is (0.0f, 0.0f)
     * @param explosion_circle used for collision calculation when cannon has been destroyed. Default value is (0.0f, 0.0f)
     * @param scale used for collision calculation. Default value is (0.0f, 0.0f)
     */
    explicit Cannon
    (
            Vector2 position = Vector2(),
            Vector2 shoot_position_offset = Vector2(),
            CannonType cannon_type = CannonType::N,
            CollisionCircle collision_circle = CollisionCircle(),
            CollisionCircle explosion_circle = CollisionCircle(),
            Vector2 scale = Vector2()
                    )
    : GameObject(position, std::move(collision_circle), Type::CANNON, scale),
    explosion_circle(std::move(explosion_circle)), type(cannon_type), shoot_position_offset(shoot_position_offset)
    {
    }

    /** Updates the position of the Cannon instance. Called when tile position is changed.
     *
     * @param offset Offset value used for setting the new position value.
     */
    void update_position(Vector2& offset);

    /**
     * Called when Cannon has been destroyed. Changes the collision circle
     */
    void check_state();



};



#endif
