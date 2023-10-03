#ifndef SPRITESHEETLOADER_H
#define SPRITESHEETLOADER_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

class SpriteSheetLoader
{
public:
    static SDL_Surface* load_sprite_sheet_surface(std::string path);

    static void free_sprite_sheet_surface(SDL_Surface* sprite_sheet);

};



#endif
