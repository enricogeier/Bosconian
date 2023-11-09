#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <utility>
#include <vector>
#include "Vector2.h"
#include "Rectangle.h"

class GameObject
{
public:

    Vector2 position;

    std::vector<Rectangle> normal_sprites;
    std::vector<Rectangle> explosion_sprite;


    explicit GameObject(Vector2 position, std::vector<Rectangle> normal_sprites, std::vector<Rectangle> explosion_sprite)
    : position(position), normal_sprites(std::move(normal_sprites)), explosion_sprite(std::move(explosion_sprite))
    {
    }


};


#endif