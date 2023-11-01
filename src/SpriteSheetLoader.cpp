#include "SpriteSheetLoader.h"

void SpriteSheetLoader::load_sprite_sheet_surface(Renderer& renderer, std::string path)
{
    // Initialize PNG loading
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface* sprite_sheet_surface = IMG_Load(path.c_str());
    if(sprite_sheet_surface == nullptr)
    {
        std::cerr << "sprite sheet could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_Texture* sprite_sheet_texture = renderer.render_sprite_sheet(sprite_sheet_surface);

    SDL_FreeSurface(sprite_sheet_surface);
    sprite_sheet_surface = nullptr;

    renderer.set_sprite_sheet_texture(sprite_sheet_texture);

}
