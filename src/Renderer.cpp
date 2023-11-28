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

    load_sprite_sheet();

}

Renderer::~Renderer()
{
    clear();
}

void Renderer::load_sprite_sheet()
{
    // Initialize PNG loading
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface* sprite_sheet_surface = IMG_Load(PATH_TO_SPRITE_SHEET.c_str());
    if(sprite_sheet_surface == nullptr)
    {
        std::cerr << "sprite sheet could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* sprite_sheet = SDL_CreateTextureFromSurface(renderer, sprite_sheet_surface);
    if(sprite_sheet == nullptr)
    {
        std::cerr << "Could not create sprite sheet texture! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(sprite_sheet_surface);
    sprite_sheet_surface = nullptr;

    sprite_sheet_texture = sprite_sheet;
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

void Renderer::render_collision_box(GameObject &game_object)
{
    // TODO: delete

    /*
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y -  camera.y,
            game_object.collision_circle.origin.x + game_object.collision_circle.radius - camera.x,
            game_object.collision_circle.origin.y - camera.y
            );
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - camera.y,
            game_object.collision_circle.origin.x - game_object.collision_circle.radius - camera.x,
            game_object.collision_circle.origin.y - camera.y
    );
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - camera.y,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y + game_object.collision_circle.radius  - camera.y
    );
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - camera.y,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - game_object.collision_circle.radius  - camera.y
    );

    */


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

std::vector<Rectangle> Renderer::get_player_sprites()
{
    std::vector<Rectangle> sprite_list;

    sprite_list.push_back(sprites[0]);
    sprite_list.push_back(sprites[1]);

    return sprite_list;
}

std::vector<Rectangle> Renderer::get_e_type(bool leader)
{
    std::vector<Rectangle> sprite_list;

    if(!leader)
    {
        sprite_list.push_back(sprites[2]);
        sprite_list.push_back(sprites[3]);
        sprite_list.push_back(sprites[4]);
        sprite_list.push_back(sprites[5]);
        sprite_list.push_back(sprites[6]);
        sprite_list.push_back(sprites[7]);
    }
    else
    {
        sprite_list.push_back(sprites[8]);
        sprite_list.push_back(sprites[9]);
        sprite_list.push_back(sprites[10]);
        sprite_list.push_back(sprites[11]);
        sprite_list.push_back(sprites[12]);
        sprite_list.push_back(sprites[13]);

    }
    return sprite_list;
}

std::vector<Rectangle> Renderer::get_i_type(bool leader)
{
    std::vector<Rectangle> sprite_list;

    if(!leader)
    {
        sprite_list.push_back(sprites[14]);
        sprite_list.push_back(sprites[15]);
        sprite_list.push_back(sprites[16]);
        sprite_list.push_back(sprites[17]);
        sprite_list.push_back(sprites[18]);
        sprite_list.push_back(sprites[19]);
    }
    else
    {
        sprite_list.push_back(sprites[20]);
        sprite_list.push_back(sprites[21]);
        sprite_list.push_back(sprites[22]);
        sprite_list.push_back(sprites[23]);
        sprite_list.push_back(sprites[24]);
        sprite_list.push_back(sprites[25]);

    }
    return sprite_list;
}

std::vector<Rectangle> Renderer::get_p_type(bool leader)
{
    std::vector<Rectangle> sprite_list;

    if(!leader)
    {
        sprite_list.push_back(sprites[26]);
        sprite_list.push_back(sprites[27]);
        sprite_list.push_back(sprites[28]);
        sprite_list.push_back(sprites[29]);
        sprite_list.push_back(sprites[30]);
        sprite_list.push_back(sprites[31]);
    }
    else
    {
        sprite_list.push_back(sprites[32]);
        sprite_list.push_back(sprites[33]);
        sprite_list.push_back(sprites[34]);
        sprite_list.push_back(sprites[35]);
        sprite_list.push_back(sprites[36]);
        sprite_list.push_back(sprites[37]);

    }
    return sprite_list;
}

std::vector<Rectangle> Renderer::get_spy()
{
    std::vector<Rectangle> sprite_list;

    sprite_list.push_back(sprites[38]);
    sprite_list.push_back(sprites[39]);
    sprite_list.push_back(sprites[40]);
    sprite_list.push_back(sprites[41]);
    sprite_list.push_back(sprites[42]);
    sprite_list.push_back(sprites[43]);

    return sprite_list;
}

std::vector<Rectangle> Renderer::get_mine()
{
    std::vector<Rectangle> sprite_list;

    sprite_list.push_back(sprites[44]);
    return sprite_list;
}

std::vector<Rectangle> Renderer::get_asteroid(short sprite)
{
    if(sprite >= 0 && sprite < 3)
    {
        std::vector<Rectangle> sprite_list;

        sprite_list.push_back(sprites[45 +  sprite]);
        return sprite_list;
    }
    else
    {
        std::cerr << "wrong sprite number for get_asteroid()" << std::endl;
    }
}

Rectangle Renderer::get_p1_life()
{
    return sprites[48];
}

Rectangle Renderer::get_p2_life()
{
    return sprites[49];
}

std::vector<Rectangle> Renderer::get_explosion_1()
{
    std::vector<Rectangle> sprite_list;

    sprite_list.push_back(sprites[50]);
    sprite_list.push_back(sprites[51]);
    sprite_list.push_back(sprites[52]);

    return sprite_list;
}

std::vector<Rectangle> Renderer::get_p1_shoot()
{
    std::vector<Rectangle> sprite_list;

    sprite_list.push_back(sprites[53]);
    sprite_list.push_back(sprites[54]);
    sprite_list.push_back(sprites[55]);
    sprite_list.push_back(sprites[56]);

    return sprite_list;
}

std::vector<Rectangle> Renderer::get_p2_shoot()
{
    std::vector<Rectangle> sprite_list;

    sprite_list.push_back(sprites[57]);
    sprite_list.push_back(sprites[58]);
    sprite_list.push_back(sprites[59]);
    sprite_list.push_back(sprites[60]);

    return sprite_list;
}