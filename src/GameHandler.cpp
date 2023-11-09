#include "GameHandler.h"


void GameHandler::initialize()
{
    player = Player(Vector2(0.0f, -1.0f));
    level.initialize_tile_index(player.position);
    load_sprite_sheet();
    this->quit_game = false;
    player.sprites = SpriteSheet::get_player_sprites();

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

        Vector2 player_sprite_size((float)player.sprites.front().w, (float)player.sprites.front().h);
        renderer.update_camera(player.position, player_sprite_size);

        // calculate objects

        // render background

        // render bullets
        for(auto bullet = bullet_list.begin(); bullet != bullet_list.end();)
        {
            float border = 1000.0f;

            if(Vector2::distance(player.position, bullet->position) > border)
            {
                bullet = bullet_list.erase(bullet);
            }
            else
            {

                if(bullet->speed != 1200 && bullet->direction == player.clamped_direction)
                {
                    bullet->speed *= 2;
                }
                else if(bullet->speed == 1200 && bullet->direction != player.clamped_direction)
                {
                    bullet->speed /= 2;
                }

                bullet->move(delta);
                SDL_Rect bullet_sprite = {bullet->sprite.x, bullet->sprite.y, bullet->sprite.w, bullet->sprite.h};
                renderer.render(bullet->position, &bullet_sprite);

                ++bullet;
            }

        }


        // render player
        match_player_direction(shoot);



        // render objects
        std::vector<GameObject> objects = level.get_all_game_objects();

        for(auto& object : objects)
        {
            // testing: always take first sprite of object
            SDL_Rect sprite{
                object.normal_sprites[0].x,
                object.normal_sprites[0].y,
                object.normal_sprites[0].w,
                object.normal_sprites[0].h
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
    short y_precision = 5;

    switch ((int)player.direction.x)
    {
        case 1:
            switch ((int)player.direction.y)
            {
                case 1:
                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + 5, player.position.y),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[1]
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.sprites.back().w + 5,
                                        player.position.y + player.sprites.back().h - 1),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[1]
                        ));

                        bullet_list.back().speed *= 2;


                    }



                    player_sprite = {
                            player.sprites.back().x,
                            player.sprites.back().y,
                            player.sprites.back().w,
                            player.sprites.back().h

                    };

                    renderer.render(player.position, &player_sprite, 180.0f);
                    break;
                case 0:
                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 15, player.position.y + (player.sprites.back().h / 2) - y_precision ),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[2]
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.sprites.back().w,
                                        player.position.y + (player.sprites.back().h / 2) - y_precision),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[2]
                        ));

                        bullet_list.back().speed *= 2;
                    }


                    player_sprite = {
                            player.sprites.front().x,
                            player.sprites.front().y,
                            player.sprites.front().w,
                            player.sprites.front().h

                    };

                    renderer.render(player.position, &player_sprite, 90.0f);
                    break;
                case -1:

                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.sprites.back().w - 12, player.position.y),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[3]
                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 12,
                                        player.position.y + player.sprites.back().h - 1),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[3]
                        ));

                    }

                    player_sprite = {
                            player.sprites.back().x,
                            player.sprites.back().y,
                            player.sprites.back().w,
                            player.sprites.back().h

                    };

                    renderer.render(player.position,  &player_sprite,90.0f);
                    break;
            }
            break;
        case 0:

            player_sprite = {
                    player.sprites.front().x,
                    player.sprites.front().y,
                    player.sprites.front().w,
                    player.sprites.front().h

            };

            switch ((int)player.direction.y)
            {
                case 1:
                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.sprites.back().w / 2) , player.position.y - 15),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[0]
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.sprites.back().w / 2) , player.position.y + player.sprites.back().h),
                                Vector2(0, 1),
                                SpriteSheet::get_p1_shoot()[0]
                        ));

                        bullet_list.back().speed *= 2;
                    }

                    renderer.render(player.position,  &player_sprite, 180.0f);
                    break;
                case -1:
                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.sprites.back().w / 2) - y_precision, player.position.y - 15),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[0]
                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.sprites.back().w / 2) - y_precision, player.position.y + player.sprites.back().h),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[0]
                        ));
                    }

                    renderer.render(player.position, &player_sprite, 0.0f);
                    break;
            }
            break;
        case -1:
            switch ((int)player.direction.y)
            {
                case 1:

                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.sprites.back().w - 5, player.position.y),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[3]
                        ));



                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 5,
                                        player.position.y + player.sprites.back().h - 1),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[3]
                        ));

                        bullet_list.back().speed *= 2;

                    }

                    player_sprite = {
                            player.sprites.back().x,
                            player.sprites.back().y,
                            player.sprites.back().w,
                            player.sprites.back().h

                    };

                    renderer.render(player.position,  &player_sprite, -90.0f);
                    break;
                case 0:

                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x, player.position.y + (player.sprites.back().h / 2) - y_precision ),
                                        player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[2]
                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.sprites.back().w, player.position.y + (player.sprites.back().h / 2) - y_precision ),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[2]
                        ));
                    }


                    player_sprite = {
                            player.sprites.front().x,
                            player.sprites.front().y,
                            player.sprites.front().w,
                            player.sprites.front().h

                    };

                    renderer.render(player.position,  &player_sprite, -90.0f);
                    break;
                case -1:

                    if(shoot)
                    {
                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x, player.position.y),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[1]
                        ));

                        bullet_list.back().speed *= 2;


                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.sprites.back().w,
                                        player.position.y + player.sprites.back().h - 1),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[1]
                        ));





                    }



                    player_sprite = {
                            player.sprites.back().x,
                            player.sprites.back().y,
                            player.sprites.back().w,
                            player.sprites.back().h

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