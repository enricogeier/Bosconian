#include "GameHandler.h"

GameHandler::GameHandler()
{
    player = Player(Vector2(640 / 2, 480 / 2), Vector2(0.0f, -1.0f), 3, 0.125f, 0.0125f);

}

void GameHandler::initialize()
{
    load_sprite_sheet();
    this->quit_game = false;
    this->player_sprites = SpriteSheet::get_player_sprites();
}

void GameHandler::game_loop()
{
    while(!this->quit_game)
    {
        renderer.clear_screen();

        handle_input();
        player.move(keyboard_input_vector);
        match_input_vector();








        renderer.update_screen();
    }
}

void GameHandler::match_input_vector()
{
    switch ((int)player.direction.x)
    {
        case 1:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render_and_rotate((int)player.position.x, (int)player.position.y, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f);
                    break;
                case 0:
                    renderer.render_and_rotate((int)player.position.x, (int)player.position.y, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f);
                    break;
                case -1:
                    renderer.render_and_rotate((int)player.position.x, (int)player.position.y, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f);
                    break;
            }
            break;
        case 0:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render_and_rotate((int)player.position.x, (int)player.position.y, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f);
                    break;
                case -1:
                    renderer.render((int)player.position.x, (int)player.position.y, &this->player_sprites.front(), SpriteSheet::get_sprite_sheet_texture());
                    break;
            }
            break;
        case -1:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render_and_rotate((int)player.position.x, (int)player.position.y, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f);
                    break;
                case 0:
                    renderer.render_and_rotate((int)player.position.x, (int)player.position.y, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f);
                    break;
                case -1:
                    renderer.render((int)player.position.x, (int)player.position.y, &this->player_sprites.back(), SpriteSheet::get_sprite_sheet_texture());
                    break;
            }
            break;

    }
}

void GameHandler::load_sprite_sheet()
{
    SDL_Surface* sprite_sheet_surface = SpriteSheetLoader::load_sprite_sheet_surface(SpriteSheet::PATH_TO_SPRITE_SHEET);
    SDL_Texture* sprite_sheet_texture = renderer.render_sprite_sheet(sprite_sheet_surface);
    SpriteSheetLoader::free_sprite_sheet_surface(sprite_sheet_surface);
    SpriteSheet::set_sprite_sheet_texture(sprite_sheet_texture);
}

void GameHandler::handle_input()
{
    SDL_Event e;

    this->keyboard_input_vector.x = 0.0f;
    this->keyboard_input_vector.y = 0.0f;

    // Handle events on queue. SDL's internal keystates are updated every time SDL PollEvent is called
    while(SDL_PollEvent(&e)) {

        // User requests quit
        if (e.type == SDL_QUIT) {
            this->quit_game = true;
            return;

        }
        else if(e.type == SDL_KEYDOWN)
        {
        }




    }

    const Uint8* current_key_state =  SDL_GetKeyboardState(NULL);

    if(current_key_state[SDL_SCANCODE_UP])
    {
        this->keyboard_input_vector.y = -1.0f;
    }
    if(current_key_state[SDL_SCANCODE_DOWN])
    {
        this->keyboard_input_vector.y = 1.0f;
    }
    if(current_key_state[SDL_SCANCODE_LEFT])
    {
        this->keyboard_input_vector.x = -1.0f;
    }
    if(current_key_state[SDL_SCANCODE_RIGHT])
    {
        this->keyboard_input_vector.x = 1.0f;
    }



}

void GameHandler::run()
{
    initialize();

    game_loop();

    renderer.clear();

}