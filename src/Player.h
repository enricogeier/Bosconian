#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Vector2.h"

class Player
{
public:

    int lives{};

    Vector2 position;
    Vector2 direction;

    float max_velocity{};
    float min_velocity{};

    SDL_Surface* sprite{}; // will be changed in the future

    explicit Player(Vector2 position = Vector2(0.0f, 0.0f), Vector2 direction = Vector2(0.0f, 0.0f),
           int lives = 3, float max_velocity = 0.0125f, float min_velocity = 0.0125f);

    void move(Vector2& new_direction);

};


#endif