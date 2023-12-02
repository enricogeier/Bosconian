#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include <utility>
#include "GameObject.h"


class Enemy : public GameObject
{
private:
    bool leader_of_formation = false;
public:

    Vector2 start_position;
    Vector2 direction;


    explicit Enemy(Vector2 position, CollisionCircle collision_circle, Vector2 direction = Vector2(), Type type = Type::E_TYPE, Vector2 scale = Vector2(1.0f, 1.0f))
    : GameObject(position, std::move(collision_circle), type, scale), direction(direction)
    {
    }

    void move(Vector2& move_direction, float& delta);

};


#endif
