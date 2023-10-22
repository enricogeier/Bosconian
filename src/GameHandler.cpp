#include "GameHandler.h"

GameHandler::GameHandler()
{
    player = Player(Vector2(0.0f, -1.0f), PLAYER_LIVES);

}

void GameHandler::initialize()
{
    current_screen_width = SCREEN_SIZE_WIDTH;
    current_screen_height = SCREEN_SIZE_HEIGHT;
    current_screen_scale_x = 1.0f;
    current_screen_scale_y = 1.0f;
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

        Vector2 camera_position((player.position.x  + ((float)player_sprites.front().w / 2)) - ((float)current_screen_width / 2),
                                (player.position.y  + ((float)player_sprites.front().h / 2)) - ((float)current_screen_height / 2));

        match_input_vector(camera_position);








        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }
}

void GameHandler::match_input_vector(Vector2& camera_position)
{

    Vector2 scale(sprite_scale);


    switch ((int)player.direction.x)
    {
        case 1:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position, camera_position, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f, scale);
                    break;
                case 0:
                    renderer.render(player.position, camera_position, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f, scale);
                    break;
                case -1:
                    renderer.render(player.position, camera_position, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), 90.0f, scale);
                    break;
            }
            break;
        case 0:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position, camera_position, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), 180.0f, scale);
                    break;
                case -1:
                    renderer.render(player.position, camera_position, &this->player_sprites.front(),
                                    SpriteSheet::get_sprite_sheet_texture(), 0.0f, scale);
                    break;
            }
            break;
        case -1:
            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position, camera_position, &this->player_sprites.back(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f, scale);
                    break;
                case 0:
                    renderer.render(player.position, camera_position, &this->player_sprites.front(),
                                               SpriteSheet::get_sprite_sheet_texture(), -90.0f, scale);
                    break;
                case -1:
                    renderer.render(player.position, camera_position, &this->player_sprites.back(),
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



void GameHandler::run() {

    initialize();

    game_loop();

    renderer.clear();

}