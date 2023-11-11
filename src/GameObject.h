#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <utility>
#include <vector>
#include "Vector2.h"
#include "Rectangle.h"
#include "CollisionCircle.h"

enum class State{
    NORMAL,
    DESTROY
};



class GameObject
{
public:

    Vector2 position;
    CollisionCircle collision_circle;
    std::vector<Rectangle> normal_sprites;
    State state = State::NORMAL;

    explicit GameObject(Vector2 position, std::vector<Rectangle> normal_sprites, CollisionCircle collision_circle)
    : position(position), normal_sprites(std::move(normal_sprites)),
      collision_circle(std::move(collision_circle))
    {
    }

    virtual ~GameObject()= default;


};


#endif