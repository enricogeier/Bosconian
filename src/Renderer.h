#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <iostream>
#include "Player.h"
#include "SpriteSheet.h"


class Renderer
{
private:
    const int SCREEN_SIZE_WIDTH = 1920;   // small: 960
    const int SCREEN_SIZE_HEIGHT = 1080; // 540

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Vector2 camera;
    Vector2 scale = Vector2(4.0f, 4.0f);

public:

    Renderer();

    ~Renderer();

    void clear_screen();

    void update_screen();

    void render(Vector2& screen_position, SDL_Rect* sprite,
                SDL_Texture* sprite_sheet_texture, float rotation = 0.0f);

    SDL_Texture* render_sprite_sheet(SDL_Surface* sprite_sheet_surface);

    void update_camera(Vector2& player_position, Vector2& sprite_size);

    void clear();

};



#endif