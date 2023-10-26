#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL.h>
#include <string>
#include <list>

class SpriteSheet
{
private:

   static SDL_Texture* sprite_sheet_texture;

public:
    const static int SPRITE_SHEET_WIDTH = 256;
    const static int SPRITE_SHEET_HEIGHT = 400;
    const static std::string PATH_TO_SPRITE_SHEET;

    // constexpr: value is known at compile-time => for compiler
    constexpr static SDL_Rect sprites[256] = {
            {0, 0, 16, 16}, // player normal
            {16, 0, 16, 16}, // player diagonal

    };



    static void set_sprite_sheet_texture(SDL_Texture* texture)
    {
        if(sprite_sheet_texture == nullptr)
        {
            SpriteSheet::sprite_sheet_texture = texture;
        }

    }

    static SDL_Texture* get_sprite_sheet_texture()
    {
        return SpriteSheet::sprite_sheet_texture;
    }

    static std::list<SDL_Rect> get_player_sprites()
    {
        std::list<SDL_Rect> sprite_list;
        sprite_list.push_back(sprites[0]);
        sprite_list.push_back(sprites[1]);

        return sprite_list;

    }







};

#endif
