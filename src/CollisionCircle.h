#ifndef COLLISIONCIRCLE_H
#define COLLISIONCIRCLE_H

#include <list>
#include <utility>
#include "Vector2.h"

enum class Layer
{
    PLAYER,
    ENEMY,
    PLAYER_BULLET,
    ENEMY_BULLET,
    CELESTIAL_OBJECT
};



class CollisionCircle
{
public:
    Vector2 origin;
    float radius;

    Layer layer;
    std::list<Layer> can_collide_with;

    explicit CollisionCircle(Vector2 origin = Vector2(), float radius = 0.0f, Layer layer = Layer::PLAYER, std::list<Layer> can_collide_with = {})
    : origin(origin), radius(radius), layer(layer), can_collide_with(std::move(can_collide_with))
    {
    }


};

#endif
