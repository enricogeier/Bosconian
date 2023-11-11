#ifndef BULLET_H
#define BULLET_H

#include <utility>

#include "GameObject.h"

class Bullet : public GameObject
{

public:
    Vector2 direction;
    int speed = 600; // default: 600


    // constructor receives CLAMPED DIRECTION!
    Bullet(Vector2 position, Vector2 direction, Rectangle normal_sprite, CollisionCircle collision_circle) :
    GameObject(position, std::vector<Rectangle>{normal_sprite}, std::move(collision_circle)), direction(direction)
    {
    }

    void move(float& delta);


};

#endif