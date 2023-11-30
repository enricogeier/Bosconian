#ifndef BULLET_H
#define BULLET_H

#include <utility>

#include "GameObject.h"

class Bullet : public GameObject
{

public:
    Vector2 clamped_direction;
    Vector2 direction;

    int speed = 600; // default: 600



    // constructor receives CLAMPED DIRECTION!
    Bullet(Vector2 position, Vector2 bullet_direction, CollisionCircle collision_circle) :
    GameObject(position, std::move(collision_circle), Type::BULLET), clamped_direction(bullet_direction)
    {
        if(bullet_direction.x > 0.0f)
        {
            direction.x = 1.0f;
        }
        else if(bullet_direction.x == 0.0f)
        {
            direction.x = 0.0f;
        }
        else
        {
            direction.x = -1.0f;
        }

        if(bullet_direction.y > 0.0f)
        {
            direction.y = 1.0f;
        }
        else if(bullet_direction.y == 0.0f)
        {
            direction.y = 0.0f;
        }
        else
        {
            direction.y = -1.0f;
        }


    }

    void move(float& delta);


};

#endif