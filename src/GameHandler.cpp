#include "GameHandler.h"

GameHandler::GameHandler()
{
    player = Player(Vector2(PLAYER_START_X, PLAYER_START_Y),
                    Vector2(0.0f, -1.0f), PLAYER_LIVES, MAX_VELOCITY, MIN_VELOCITY);

}

void GameHandler::initialize()
{
    load_sprite_sheet();
    this->quit_game = false;
    this->player_sprites = SpriteSheet::get_player_sprites();






    fps_timer.start();
}

void GameHandler::game_loop()
{
    while(!this->quit_game)
    {

        renderer.clear_screen();

        float delta = fps_timer.get_delta();



        handle_input();
        player.move(keyboard_input_vector, delta);
        match_input_vector();




        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }
}

void GameHandler::match_input_vector()
{
    Vector2 scale(4.0f, 4.0f);


    switch ((int)player.direction.x)
    {
        case 1:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f, scale);
                    break;
                case 0:
                    renderer.render(player.position, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f, scale);
                    break;
                case -1:
                    renderer.render(player.position, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f, scale);
                    break;
            }
            break;
        case 0:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f, scale);
                    break;
                case -1:
                    renderer.render(player.position, &this->player_sprites.front(),
                                    SpriteSheet::get_sprite_sheet_texture(), 0.0f, scale);
                    break;
            }
            break;
        case -1:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f, scale);
                    break;
                case 0:
                    renderer.render(player.position, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f, scale);
                    break;
                case -1:
                    renderer.render(player.position, &this->player_sprites.back(),
                                    SpriteSheet::get_sprite_sheet_texture(), 0.0f, scale);
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
        else if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {



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




    }

    /*


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

    */

}

void GameHandler::run() {

    initialize();

    game_loop();

    renderer.clear();

}