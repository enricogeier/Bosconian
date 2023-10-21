#include "Renderer.h"

Renderer::Renderer()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // create window
    window = SDL_CreateWindow("Bosconian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, SDL_WINDOW_RESIZABLE);

    // create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize renderer color. Set the color used for drawing operations (Rect, Line and Clear).
    // Set the color for drawing or filling rectangles, lines, and points, and for SDL_RenderClear().
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

}

Renderer::~Renderer()
{
    clear();
}

void Renderer::clear_screen()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
}

void Renderer::update_screen()
{
    // Update screen
    SDL_RenderPresent(renderer);
}

void Renderer::update_logical_size()
{
    SDL_RenderSetLogicalSize(renderer, current_screen_width, current_screen_height);
}

void Renderer::render(Vector2& position, Vector2& camera_position, SDL_Rect* sprite, SDL_Texture* sprite_sheet_texture, float rotation, Vector2 scale)
{
    // for testing
    SDL_Rect rect = {-32 - (int)camera_position.x, -32 - (int)camera_position.y, current_screen_width / 8, current_screen_height / 8}; // -32, -32
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &rect);



    SDL_Rect render_quad = {(int)(position.x - camera_position.x), (int)(position.y - camera_position.y),
                             sprite->w * (int)scale.x, sprite->h * (int)scale.y};

    SDL_RenderCopyEx(renderer, sprite_sheet_texture, sprite, &render_quad, rotation, nullptr, SDL_FLIP_NONE);

}



SDL_Texture *Renderer::render_sprite_sheet(SDL_Surface *sprite_sheet_surface)
{
    SDL_Texture* sprite_sheet = SDL_CreateTextureFromSurface(renderer, sprite_sheet_surface);
    if(sprite_sheet == nullptr)
    {
        std::cerr << "Could not create sprite sheet texture! SDL Error: " << SDL_GetError() << std::endl;
    }

    return sprite_sheet;

}

void Renderer::clear()
{
    // destroy sprite sheet
    SDL_Texture* sprite_sheet_texture = SpriteSheet::get_sprite_sheet_texture();

    if(sprite_sheet_texture != nullptr)
    {
        SDL_DestroyTexture(sprite_sheet_texture);
        sprite_sheet_texture = nullptr;
    }

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}