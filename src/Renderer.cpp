#include "Renderer.h"

Renderer::Renderer()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // create window
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, SDL_WINDOW_SHOWN);

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

void Renderer::set_sprite_sheet_texture(SDL_Texture *texture)
{
    sprite_sheet_texture = texture;
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

void Renderer::render_background_particle(SDL_Rect rectangle, short r, short g, short b, short a)
{
    rectangle.x -= camera.x;
    rectangle.y -= camera.y;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rectangle);

}


void Renderer::render(Vector2& position, SDL_Rect* sprite, float rotation)
{

    SDL_Rect render_quad = {(int)(position.x - camera.x), (int)(position.y - camera.y),
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

void Renderer::update_camera(Vector2 &player_position, Vector2 &sprite_size)
{
    camera = Vector2((player_position.x + (sprite_size.x / 2)) - ((float)SCREEN_SIZE_WIDTH / 2),
                     (player_position.y + (sprite_size.y / 2)) - ((float)SCREEN_SIZE_HEIGHT / 2));
}


void Renderer::clear()
{
    // destroy sprite sheet

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