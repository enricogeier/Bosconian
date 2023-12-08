#ifndef CANNON_H
#define CANNON_H

#include <utility>
#include <vector>
#include "GameObject.h"


class Cannon : public GameObject
{
private:
    bool exploded = false;


public:

    explicit Cannon
    (
            Vector2 position = Vector2(),
            CollisionCircle collision_circle = CollisionCircle(),
            Vector2 scale = Vector2()
                    )
    : GameObject(position, std::move(collision_circle), Type::CANNON, scale)
    {
    }
};



#endif
