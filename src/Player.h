#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "vector2.h"

class Player
{
public:

    int lives{};

    Vector2 position;
    Vector2 direction;

    float max_velocity{};
    float min_velocity{};

    SDL_Surface* sprite{}; // will be changed in the future

    Player(Vector2 position, Vector2 direction, int lives, float max_velocity, float min_velocity);

    ~Player();

    void render(SDL_Renderer* renderer);

    void free();

    void move(Vector2& new_direction);

};


#endif