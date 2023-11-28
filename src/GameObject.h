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
    DESTROY
};



class GameObject
{
public:

    Vector2 position;
    CollisionCircle collision_circle;
    std::vector<Rectangle> normal_sprites;
    State state = State::NORMAL;

    unsigned int id;
    static unsigned int id_counter;


    explicit GameObject(Vector2 position, std::vector<Rectangle> normal_sprites, CollisionCircle collision_circle)
    : position(position), normal_sprites(std::move(normal_sprites)),
      collision_circle(std::move(collision_circle))
    {
        id = id_counter++;
    }

    bool operator==(const GameObject& other) const
    {
        return this->id == other.id;
    }

    virtual ~GameObject()= default;


};


#endif