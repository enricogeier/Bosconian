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
    // origin: position of collision circle's center
    Vector2 origin;
    // position_in_sprite: position of collision circle's center in local space
    Vector2 initial_origin;

    float radius;



    Layer layer;
    std::list<Layer> can_collide_with;

    explicit CollisionCircle(Vector2 origin = Vector2(), float radius = 0.0f, Layer layer = Layer::PLAYER, std::list<Layer> can_collide_with = {}, Vector2 scale = Vector2(1.0f, 1.0f))
    : origin(origin), radius(radius), layer(layer), can_collide_with(std::move(can_collide_with)), initial_origin(origin)
    {
    }

    bool operator==(const CollisionCircle& other) const
    {
        return this->origin == other.origin && this->initial_origin == other.initial_origin
        && this->radius == other.radius && this->layer == other.layer && this->can_collide_with == other.can_collide_with;
    }

};

#endif
