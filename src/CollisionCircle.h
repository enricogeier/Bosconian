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
    Vector2 position_in_sprite;

    float radius;



    Layer layer;
    std::list<Layer> can_collide_with;

    explicit CollisionCircle(Vector2 origin = Vector2(), float radius = 0.0f, Layer layer = Layer::PLAYER, std::list<Layer> can_collide_with = {}, Vector2 scale = Vector2(1.0f, 1.0f))
    : origin(origin), radius(radius), layer(layer), can_collide_with(std::move(can_collide_with)), position_in_sprite(origin)
    {
    }

};

#endif
