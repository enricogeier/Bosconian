#ifndef BULLET_H
#define BULLET_H

#include "Vector2.h"
#include "Rectangle.h"

class Bullet
{

public:
    Vector2 direction;
    int speed = 600; // default: 600
    Vector2 position;
    Rectangle sprite;
    // constructor receives CLAMPED DIRECTION!
    Bullet(Vector2 position, Vector2 direction, Rectangle sprite) : position(position), direction(direction), sprite(sprite)
    {
    }

    void move(float& delta)
    {
        position += direction * (float)speed * delta;
    }

};

#endif