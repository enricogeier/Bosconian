#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include <utility>
#include "GameObject.h"


class Enemy : public GameObject
{
private:

    const float VELOCITY = 350.0f;
    const float VALUE_LESS_THAN_0[4] = {-1.0f, -0.67f, -0.33f, 0.0f};
    const float VALUE_0_OR_HIGHER[4] = {0.0f, 0.33f, 0.67f, 1.0f};

public:

    Vector2 direction = Vector2();
    Vector2 clamped_direction = Vector2();

    /**
     * Constructs a new Enemy object.
     *
     * @param position The position of the enemy. The position value for the Enemy instance
     * @param collision_circle used for collision calculation
     * @param type represents the type of Enemy. Default value is Type::E_TYPE if not provided.
     * @param scale used for collision calculation. Default value is (1.0f, 1.0f) if not provided.
     */
    explicit Enemy(Vector2 position, CollisionCircle collision_circle, Type type = Type::E_TYPE, Vector2 scale = Vector2(1.0f, 1.0f))
    : GameObject(position, std::move(collision_circle), type, scale)
    {
    }

    /**
     * Moves the enemy. The function sets a new value for the position of the instance
     *
     * @param player_position The position of the player instance to fly to
     * @param delta Time between two frames
     */
    void move(Vector2& player_position, float& delta);

};


#endif
