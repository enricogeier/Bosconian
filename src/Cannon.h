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

    explicit Cannon
    (
            Vector2 position = Vector2(),
            CannonType cannon_type = CannonType::N,
            CollisionCircle collision_circle = CollisionCircle(),
            CollisionCircle explosion_circle = CollisionCircle(),
            Vector2 scale = Vector2()
                    )
    : GameObject(position, std::move(collision_circle), Type::CANNON, scale),
    explosion_circle(std::move(explosion_circle)), type(cannon_type)
    {
    }

    void update_position(Vector2& offset);

    void check_state();



};



#endif
