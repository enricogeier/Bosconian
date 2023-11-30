#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

#include "GameObject.h"

class Player : public GameObject
{
private:
    static const Vector2 START_POSITION;
    static const float MAX_VELOCITY;
    static const float MIN_VELOCITY;

    int player_lives = 3;

public:

    Vector2 clamped_direction;
    Vector2 direction = Vector2(0.0f, -1.0f);

    explicit Player(CollisionCircle collisionCircle = CollisionCircle())
    : GameObject(START_POSITION, std::move(collisionCircle), Type::PLAYER)
    {
    }

    void move(Vector2& new_direction, float& delta);

};


#endif