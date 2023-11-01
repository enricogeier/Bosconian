#ifndef SPRITESHEET_H
#define SPRITESHEET_H


#include <string>
#include <list>
#include "Player.h"

class SpriteSheet
{

public:
    const static int SPRITE_SHEET_WIDTH = 256;
    const static int SPRITE_SHEET_HEIGHT = 400;
    const static std::string PATH_TO_SPRITE_SHEET;

    // constexpr: value is known at compile-time => for compiler
    constexpr static Rectangle sprites[256] = {
            {0, 0, 16, 16}, // player normal
            {16, 0, 16, 16}, // player diagonal

    };



    static std::list<Rectangle> get_player_sprites()
    {
        std::list<Rectangle> sprite_list;
        sprite_list.push_back(sprites[0]);
        sprite_list.push_back(sprites[1]);

        return sprite_list;

    }


};

#endif
