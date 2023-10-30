#include "GameHandler.h"


void GameHandler::initialize()
{
    player = Player(Vector2(0.0f, -1.0f));
    level.initialize_tile_index(player.position);
    load_sprite_sheet();
    this->quit_game = false;
    this->player_sprites = SpriteSheet::get_player_sprites();
}

void GameHandler::game_loop()
{
    fps_timer.start();
    while(!this->quit_game)
    {

        renderer.clear_screen();

        float delta = fps_timer.get_delta();

        if(Input::handle_user_input(this->keyboard_input_vector, this->frame_counter, this->renderer))
        {
            return;
        }

        player.move(keyboard_input_vector, delta);
        level.set_current_tile(player.position); // rearrange tiles

        Vector2 player_sprite_size((float)player_sprites.front().w, (float)player_sprites.front().h);
        renderer.update_camera(player.position, player_sprite_size);

        {

            // render background particles, for testing
            std::list<Vector4> test = level.test();

            // 0 -> RED
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0xFF, 0x00, 0x00, 0xFF);
            test.pop_front();

            // 1 -> GREEN
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0x00, 0xFF, 0x00, 0xFF);
            test.pop_front();

            // 2 -> BLUE
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0x00, 0x00, 0xFF, 0xFF);
            test.pop_front();


            // 3 -> YELLOW
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0xFF, 0xFF, 0x00, 0xFF);
            test.pop_front();

            // 4 -> MAGENTA
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0xFF, 0x00, 0xFF, 0xFF);
            test.pop_front();

            // 5 -> CYAN
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0x00, 0xFF, 0xFF, 0xFF);
            test.pop_front();

            // 6 -> WHITE
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0xFF, 0xFF, 0xFF, 0xFF);
            test.pop_front();

            // 7 -> BLACK
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0x00, 0x00, 0x00, 0xFF);
            test.pop_front();

            // 8 -> ORANGE
            renderer.render_background_particle({(int)test.front().x,(int)test.front().y,(int)test.front().z,(int)test.front().w}, 0xFF, 0xAA, 0x00, 0xFF);
            test.pop_front();

            // end of test

        }
        match_input_vector();





        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

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
                    renderer.render(player.position,&this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f);
                    break;
                case 0:
                    renderer.render(player.position, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f);
                    break;
                case -1:
                    renderer.render(player.position,  &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f);
                    break;
            }
            break;
        case 0:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position,  &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f);
                    break;
                case -1:
                    renderer.render(player.position, &this->player_sprites.front(),
                                    SpriteSheet::get_sprite_sheet_texture(), 0.0f);
                    break;
            }
            break;
        case -1:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position,  &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f);
                    break;
                case 0:
                    renderer.render(player.position,  &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f);
                    break;
                case -1:
                    renderer.render(player.position,  &this->player_sprites.back(),
                                    SpriteSheet::get_sprite_sheet_texture(), 0.0f);
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



void GameHandler::run() {

    initialize();

    game_loop();

    renderer.clear();

}