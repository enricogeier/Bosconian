#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <iostream>
#include "Player.h"
#include "SpriteSheet.h"


class Renderer
{
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

public:

    Renderer();

    ~Renderer();

    void clear_screen();

    void update_screen();

    void render(int x, int y, SDL_Rect* sprite, SDL_Texture* sprite_sheet_texture);

    void render_and_rotate(int x, int y, SDL_Rect* sprite, SDL_Texture* sprite_sheet_texture, float angle = 0.0f);

    SDL_Texture* render_sprite_sheet(SDL_Surface* sprite_sheet_surface);

    void clear();

};



#endif