#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <utility>
#include <vector>
#include "Vector2.h"
#include "Rectangle.h"
#include "CollisionCircle.h"

enum class State{
    NORMAL,
    EXPLODE,
    MINE_EXPLODE,
    MINE_EXPLODED,
    DESTROY
};

enum Type
{
    PLAYER,
    E_TYPE,
    P_TYPE,
    I_TYPE,
    SPY,
    ASTEROID,
    MINE,
    SPACE_STATION,
    CANNON,
    BULLET,
};




class GameObject
{
public:

    Vector2 position;
    CollisionCircle collision_circle;
    State state = State::NORMAL;
    Type type;

    unsigned int id;
    static unsigned int id_counter;


    explicit GameObject(Vector2 position, CollisionCircle collision_circle, Type type)
    : position(position), type(type)
    {
        id = id_counter++;
        collision_circle.origin = collision_circle.initial_origin + position;
        this->collision_circle = collision_circle;
    }

    bool operator==(const GameObject& other) const
    {
        return this->id == other.id;
    }

    virtual ~GameObject()= default;


};


#endif