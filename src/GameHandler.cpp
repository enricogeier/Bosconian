#include "GameHandler.h"


void GameHandler::initialize()
{
    player = Player(Vector2(0.0f, -1.0f));
    level.initialize_tile_index(player.position);
    load_sprite_sheet();
    this->quit_game = false;
    player.player_sprites = SpriteSheet::get_player_sprites();

    // testing
    level.spawn_enemy(player.position);

}

void GameHandler::game_loop()
{
    fps_timer.start();
    while(!this->quit_game)
    {

        renderer.clear_screen();

        float delta = fps_timer.get_delta();

        bool shoot = false;
        switch (Input::handle_user_input(this->keyboard_input_vector, this->frame_counter))
        {
            case NONE:
                break;
             case SHOOT_PRESSED:
                shoot = true;
                break;
            case CLOSE_WINDOW:
                quit_game = true;
        }

        player.move(keyboard_input_vector, delta);
        level.set_current_tile(player.position); // rearrange tiles

        Vector2 player_sprite_size((float)player.player_sprites.front().w, (float)player.player_sprites.front().h);
        renderer.update_camera(player.position, player_sprite_size);

        // calculate objects

        // render background

        // render bullets
        for(auto& bullet : bullet_list)
        {
            bullet.move(delta);
            SDL_Rect bullet_sprite = {bullet.sprite.x, bullet.sprite.y, bullet.sprite.w, bullet.sprite.h};
            renderer.render(bullet.position, &bullet_sprite);
        }

        // render player
        match_player_direction(shoot);


        // render objects
        std::vector<GameObject> objects = level.get_all_game_objects();

        for(auto& object : objects)
        {
            // testing: always take first sprite of object
            SDL_Rect sprite{
                object.player_sprites[0].x,
                object.player_sprites[0].y,
                object.player_sprites[0].w,
                object.player_sprites[0].h
            };

            renderer.render(object.position, &sprite);
        }





        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }
}

void GameHandler::match_player_direction(bool& shoot)
{

    SDL_Rect player_sprite;
    short bullet_offset = 30;
    short y_precision = 5;

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
                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - bullet_offset - 15, player.position.y + (player.player_sprites.back().h / 2) - y_precision ),
                                Vector2(-1, 0),
                                SpriteSheet::get_p1_shoot()[2]
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x  + player.player_sprites.back().w + bullet_offset, player.position.y + (player.player_sprites.back().h / 2) - y_precision ),
                                Vector2(1, 0),
                                SpriteSheet::get_p1_shoot()[2]
                        ));
                    }


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
            if(shoot)
            {
                bullet_list.push_back(Bullet(
                        Vector2(player.position.x + (player.player_sprites.back().w / 2) - y_precision, player.position.y - bullet_offset - 15),
                        Vector2(0, -1),
                        SpriteSheet::get_p1_shoot()[0]
                        ));

                bullet_list.push_back(Bullet(
                        Vector2(player.position.x + (player.player_sprites.back().w / 2) - y_precision, player.position.y + player.player_sprites.back().h + bullet_offset),
                        Vector2(0, 1),
                        SpriteSheet::get_p1_shoot()[0]
                ));
            }

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

                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - bullet_offset, player.position.y + (player.player_sprites.back().h / 2) - y_precision ),
                                        Vector2(-1, 0),
                                SpriteSheet::get_p1_shoot()[2]
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x  + player.player_sprites.back().w + bullet_offset, player.position.y + (player.player_sprites.back().h / 2) - y_precision ),
                                Vector2(1, 0),
                                SpriteSheet::get_p1_shoot()[2]
                        ));
                    }


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