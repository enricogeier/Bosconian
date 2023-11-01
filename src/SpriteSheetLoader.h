#ifndef SPRITESHEETLOADER_H
#define SPRITESHEETLOADER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Renderer.h"

class SpriteSheetLoader
{
public:

    static void load_sprite_sheet_surface(Renderer& renderer, std::string path);

};



#endif
