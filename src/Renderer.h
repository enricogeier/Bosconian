#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <iostream>
#include <string>
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
    Vector2 scale;

    SDL_Texture* sprite_sheet_texture = nullptr;

    const std::string WINDOW_TITLE = "Bosconian";

public:

    Renderer();

    ~Renderer();

    void set_scale(Vector2 scale);

    void set_sprite_sheet_texture(SDL_Texture* texture);

    void clear_screen();

    void update_screen();

    void render_background_particle(SDL_Rect rectangle, short r, short g, short b, short a);

    void render(Vector2& screen_position, SDL_Rect* sprite, float rotation = 0.0f);

    void render_collision_box(GameObject& game_object);

    SDL_Texture* render_sprite_sheet(SDL_Surface* sprite_sheet_surface);

    void update_camera(Vector2& player_position, Vector2& sprite_size);

    void clear();

};



#endif