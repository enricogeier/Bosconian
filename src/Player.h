#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

#include "GameObject.h"

class Player : public GameObject
{
private:
    static const Vector2 START_POSITION;


public:

    Vector2 clamped_direction;
    Vector2 direction = Vector2(0.0f, -1.0f);

    int lives = 3;

    static const float MAX_VELOCITY;
    static const float MIN_VELOCITY;


    bool do_acceleration = false;

    static const float ACCELERATION;


    float current_velocity = MIN_VELOCITY;

    explicit Player(CollisionCircle collisionCircle = CollisionCircle(), Vector2 scale = Vector2(1.0f, 1.0f))
    : GameObject(START_POSITION, std::move(collisionCircle), Type::PLAYER, scale)
    {
    }

    void move(Vector2& new_direction, float& delta, bool& accelerate);


};



#endif