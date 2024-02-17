#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include <utility>
#include "GameObject.h"


class Enemy : public GameObject
{
private:

    const float VELOCITY = 350.0f;
    const float VALUE_LESS_THAN_0[3] = {-1.0f, -0.67f, -0.33f};
    const float VALUE_0_OR_HIGHER[4] = {0.0f, 0.33f, 0.67f, 1.0f};

public:

    Vector2 start_position;
    Vector2 direction = Vector2();
    Vector2 clamped_direction = Vector2();


    explicit Enemy(Vector2 position, CollisionCircle collision_circle, Type type = Type::E_TYPE, Vector2 scale = Vector2(1.0f, 1.0f))
    : GameObject(position, std::move(collision_circle), type, scale)
    {
    }

    void move(Vector2& player_position, float& delta);

};


#endif
