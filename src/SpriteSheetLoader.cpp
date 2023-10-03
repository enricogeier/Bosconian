#include "SpriteSheetLoader.h"

SDL_Surface* SpriteSheetLoader::load_sprite_sheet_surface(std::string path)
{
    SDL_Surface* sprite_sheet_surface = SDL_LoadBMP(path.c_str());
    if(sprite_sheet_surface == nullptr)
    {
        std::cerr << "sprite sheet could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
    }


    return sprite_sheet_surface;
}

void SpriteSheetLoader::free_sprite_sheet_surface(SDL_Surface *sprite_sheet)
{
    SDL_FreeSurface(sprite_sheet);
    sprite_sheet = nullptr;
}