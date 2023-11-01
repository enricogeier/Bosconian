#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector2.h"


class GameObject
{
private:
    Vector2 position;

public:

    explicit GameObject(Vector2 position) : position(position)
    {
    }


};


#endif