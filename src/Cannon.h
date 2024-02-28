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

    void update_position(Vector2& offset);

    void check_state();



};



#endif
