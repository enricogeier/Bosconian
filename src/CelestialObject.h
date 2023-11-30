#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <utility>
#include "GameObject.h"

enum CelestialType
{
    ASTEROID,
    MINE
};


class CelestialObject : public GameObject
{
public:
    CelestialType type;

    explicit CelestialObject(Vector2 position, CollisionCircle collision_circle, CelestialType type = CelestialType::ASTEROID)
    : GameObject(position, std::move(collision_circle)), type(type)
    {
    }


};


#endif CELESTIALOBJECT_H
