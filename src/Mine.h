#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <utility>
#include "GameObject.h"


class Mine : public GameObject
{
public:

    explicit Mine(Vector2 position, CollisionCircle collision_circle, Type type = Type::ASTEROID)
    : GameObject(position, std::move(collision_circle), type)
    {
    }


};


#endif CELESTIALOBJECT_H
