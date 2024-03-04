#ifndef BULLET_H
#define BULLET_H

#include <utility>

#include "GameObject.h"

class Bullet : public GameObject
{

public:
    Vector2 clamped_direction;
    Vector2 direction;

    int speed = 600;

    void increment(int& a);


    // constructor receives CLAMPED DIRECTION!
    Bullet(Vector2 position, Vector2 bullet_direction, CollisionCircle collision_circle, Vector2 scale = Vector2(1.0f, 1.0f), int speed = 600) :
    GameObject(position, std::move(collision_circle), Type::BULLET, scale), clamped_direction(bullet_direction)
    {
        this->speed = speed;

        if(bullet_direction.x >= 0.4f)
        {
            direction.x = 1.0f;
        }
        else if(bullet_direction.x <= -0.4f)
        {
            direction.x = -1.0f;
        }
        else
        {
            direction.x = 0.0f;
        }

        if(bullet_direction.y >= 0.4f)
        {
            direction.y = 1.0f;
        }
        else if(bullet_direction.y <= -0.4f)
        {
            direction.y = -1.0f;
        }
        else
        {
            direction.y = 0.0f;
        }

    }

    void move(float& delta);


};

#endif