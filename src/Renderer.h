#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <iostream>
#include "Settings.h"
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

    void render(Vector2& screen_position, SDL_Rect* sprite, SDL_Texture* sprite_sheet_texture, float rotation = 0.0f, Vector2 scale = Vector2(1.0f, 1.0f));

    SDL_Texture* render_sprite_sheet(SDL_Surface* sprite_sheet_surface);

    void clear();

};



#endif