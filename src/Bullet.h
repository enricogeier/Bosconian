#ifndef BULLET_H
#define BULLET_H

#include "Vector2.h"
#include "Rectangle.h"

class Bullet
{
private:
    const float SPEED = 200.0f;
    Vector2 direction;

public:
    Vector2 position;
    Rectangle sprite;
    // constructor receives CLAMPED DIRECTION!
    Bullet(Vector2 position, Vector2 direction, Rectangle sprite) : position(position), direction(direction), sprite(sprite)
    {
    }

    void move(float& delta)
    {
        position += direction * SPEED * delta;
        int a = 0;
    }

};

#endif