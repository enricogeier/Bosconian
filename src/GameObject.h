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
    DESTROY,
    PLAYER_COLLISION
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
    BULLET
};




class GameObject
{
public:

    Vector2 position;
    Vector2 scale = Vector2(1.0f, 1.0f);

    CollisionCircle collision_circle;
    State state = State::NORMAL;
    Type type;



    unsigned int id;
    static unsigned int id_counter;


    /**
     * Constructs a new GameObject object.
     *
     * @param position The position of the GameObject instance.
     * @param collision_circle used for collision calculation.
     * @param type Type of GameObject. See enum Type.
     * @param scale used for collision calculation. Default value is (1.0f, 1.0f) if not provided.
     */
    explicit GameObject(Vector2 position, CollisionCircle collision_circle, Type type, Vector2 scale = Vector2(1.0f, 1.0f))
    : position(position), type(type), scale(scale)
    {
        id = id_counter++;
        collision_circle.origin = collision_circle.initial_origin + position;
        this->collision_circle = collision_circle;
    }


    /**
     * Checks if the ID of this GameObject object is equal to the ID of another GameObject object.
     *
     * @param other The GameObject object to compare with.
     * @return true if the IDs of the two GameObject objects are equal, false otherwise.
     */
    bool operator==(const GameObject& other) const
    {
        return this->id == other.id;
    }

    virtual ~GameObject()= default;


};


#endif