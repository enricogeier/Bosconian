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

    /**
     * Constructs a new CollisionCircle object
     *
     * @param origin center of the CollisionCircle
     * @param radius radius of the CollisionCircle. Sets the size of the hitbox / hurtbox
     * @param layer represents the layer of the hitbox / hurtbox. Used in other objects for collision detection
     * @param can_collide_with sets the layers which the object can collide with
     */
    explicit CollisionCircle(Vector2 origin = Vector2(), float radius = 0.0f, Layer layer = Layer::PLAYER, std::list<Layer> can_collide_with = {})
    : origin(origin), radius(radius), layer(layer), can_collide_with(std::move(can_collide_with)), initial_origin(origin)
    {
    }

    /**
     * This function compares the origin, initial origin, radius, layer, and collision properties of this CollisionCircle
     * object with another CollisionCircle objects to determine equality.
     *
     * @param other The CollisionCircle object to compare with
     * @return true if all attributes of the two CollisionCircle objects are equal, false otherwise.
     */
    bool operator==(const CollisionCircle& other) const
    {
        return this->origin == other.origin && this->initial_origin == other.initial_origin
        && this->radius == other.radius && this->layer == other.layer && this->can_collide_with == other.can_collide_with;
    }

};

#endif
