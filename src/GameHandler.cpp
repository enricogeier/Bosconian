#include "GameHandler.h"


void GameHandler::initialize()
{
    player = Player(Vector2(0.0f, -1.0f));
    level.initialize_tile_index(player.position);
    load_sprite_sheet();
    this->quit_game = false;
    player.player_sprites = SpriteSheet::get_player_sprites();
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
            this->quit_game = true;
        }

        player.move(keyboard_input_vector, delta);
        level.set_current_tile(player.position); // rearrange tiles

        Vector2 player_sprite_size((float)player.player_sprites.front().w, (float)player.player_sprites.front().h);
        renderer.update_camera(player.position, player_sprite_size);


        // render background

        // render player
        match_input_vector();

        // calculate objects

        // render objects







        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }
}

void GameHandler::match_input_vector()
{

    SDL_Rect player_sprite;

    switch ((int)player.direction.x)
    {
        case 1:
            switch ((int)player.direction.y)
            {
                case 1:

                    player_sprite = {
                            player.player_sprites.back().x,
                            player.player_sprites.back().y,
                            player.player_sprites.back().w,
                            player.player_sprites.back().h

                    };

                    renderer.render(player.position, &player_sprite, 180.0f);
                    break;
                case 0:

                    player_sprite = {
                            player.player_sprites.front().x,
                            player.player_sprites.front().y,
                            player.player_sprites.front().w,
                            player.player_sprites.front().h

                    };

                    renderer.render(player.position, &player_sprite, 90.0f);
                    break;
                case -1:

                    player_sprite = {
                            player.player_sprites.back().x,
                            player.player_sprites.back().y,
                            player.player_sprites.back().w,
                            player.player_sprites.back().h

                    };

                    renderer.render(player.position,  &player_sprite,90.0f);
                    break;
            }
            break;
        case 0:

            player_sprite = {
                    player.player_sprites.front().x,
                    player.player_sprites.front().y,
                    player.player_sprites.front().w,
                    player.player_sprites.front().h

            };

            switch ((int)player.direction.y)
            {
                case 1:
                    renderer.render(player.position,  &player_sprite, 180.0f);
                    break;
                case -1:
                    renderer.render(player.position, &player_sprite, 0.0f);
                    break;
            }
            break;
        case -1:
            switch ((int)player.direction.y)
            {
                case 1:

                    player_sprite = {
                            player.player_sprites.back().x,
                            player.player_sprites.back().y,
                            player.player_sprites.back().w,
                            player.player_sprites.back().h

                    };

                    renderer.render(player.position,  &player_sprite, -90.0f);
                    break;
                case 0:

                    player_sprite = {
                            player.player_sprites.front().x,
                            player.player_sprites.front().y,
                            player.player_sprites.front().w,
                            player.player_sprites.front().h

                    };

                    renderer.render(player.position,  &player_sprite, -90.0f);
                    break;
                case -1:

                    player_sprite = {
                            player.player_sprites.back().x,
                            player.player_sprites.back().y,
                            player.player_sprites.back().w,
                            player.player_sprites.back().h

                    };

                    renderer.render(player.position, &player_sprite, 0.0f);
                    break;
            }
            break;

    }
}

void GameHandler::load_sprite_sheet()
{
    SpriteSheetLoader::load_sprite_sheet_surface(renderer, SpriteSheet::PATH_TO_SPRITE_SHEET);

}



void GameHandler::run() {

    initialize();

    game_loop();

    renderer.clear();

}