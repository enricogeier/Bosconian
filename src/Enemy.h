#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H

#include <utility>
#include "GameObject.h"

enum Type
{
    E_TYPE,
    P_TYPE,
    I_TYPE,
    SPY
};


class Enemy : public GameObject
{
private:
    bool leader_of_formation = false;
public:

    Vector2 start_position;
    Vector2 direction;

    Type type;


    explicit Enemy(Vector2 position, CollisionCircle collision_circle, Vector2 direction = Vector2(), Type type = Type::E_TYPE)
    : GameObject(position, std::move(collision_circle)), direction(direction), type(type)
    {
    }

    void move(Vector2& move_direction, float& delta);

};


#endif
