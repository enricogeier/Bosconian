#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Player.h"


class Renderer
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:

    ~Renderer();

    bool initialize();

    void render_player(Player& player);

    void clear();

};



#endif