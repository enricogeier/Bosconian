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


    /**
     *  Constructs a new Bullet object which represents a bullet in the game
     *
     * @param position The position of the bullet
     * @param bullet_direction The clamped direction of the bullet
     * @param collision_circle used for collision calculation
     * @param scale is used for collision calculation. Default value is (1.0f, 1.0f)
     * @param speed The speed of the bullet. Default value is 600
     */
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



    /**
     *      Moves the bullet. The function sets a new value for the position of the instance
     *
     *      * @param delta Time between two frames
     */
    void move(float& delta);


};

#endif