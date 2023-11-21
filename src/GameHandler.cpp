#include "GameHandler.h"


void GameHandler::move_bullets(float& delta)
{
    for(auto bullet = bullet_list.begin(); bullet != bullet_list.end();)
    {
        float border = 1000.0f;

        if(Vector2::distance(player.position, bullet->position) > border || bullet->state == State::DESTROY)
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
            quad_tree.insert(*bullet);

            ++bullet;
        }

    }

}


void GameHandler::check_bullet_collisions()
{
    for(auto& bullet: bullet_list)
    {
         quad_tree.check_collision(bullet);
    }
}


void GameHandler::render_bullets()
{
    for(auto& bullet : bullet_list)
    {
        SDL_Rect bullet_sprite = {
                bullet.normal_sprites.back().x,
                bullet.normal_sprites.back().y,
                bullet.normal_sprites.back().w,
                bullet.normal_sprites.back().h
        };

        renderer.render(bullet.position, &bullet_sprite);

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
                                SpriteSheet::get_p1_shoot()[1],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w + 5,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[1],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;


                    }



                    player_sprite = {
                            player.normal_sprites.back().x,
                            player.normal_sprites.back().y,
                            player.normal_sprites.back().w,
                            player.normal_sprites.back().h

                    };

                    renderer.render(player.position, &player_sprite, 180.0f);
                    break;
                case 0:
                    if(shoot)
                    {



                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 15, player.position.y + (player.normal_sprites.back().h / 2) - y_precision ),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[2],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w,
                                        player.position.y + (player.normal_sprites.back().h / 2) - y_precision),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[2],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;
                    }


                    player_sprite = {
                            player.normal_sprites.front().x,
                            player.normal_sprites.front().y,
                            player.normal_sprites.front().w,
                            player.normal_sprites.front().h

                    };

                    renderer.render(player.position, &player_sprite, 90.0f);
                    break;
                case -1:

                    if(shoot)
                    {

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w - 12, player.position.y),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[3],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 12,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[3],
                                CollisionManager::get_player_bullet_collision()
                        ));

                    }

                    player_sprite = {
                            player.normal_sprites.back().x,
                            player.normal_sprites.back().y,
                            player.normal_sprites.back().w,
                            player.normal_sprites.back().h

                    };

                    renderer.render(player.position,  &player_sprite,90.0f);
                    break;
            }
            break;
        case 0:

            player_sprite = {
                    player.normal_sprites.front().x,
                    player.normal_sprites.front().y,
                    player.normal_sprites.front().w,
                    player.normal_sprites.front().h

            };

            switch ((int)player.direction.y)
            {
                case 1:
                    if(shoot)
                    {

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.normal_sprites.back().w / 2) , player.position.y - 15),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[0],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.normal_sprites.back().w / 2) , player.position.y + player.normal_sprites.back().h),
                                Vector2(0, 1),
                                SpriteSheet::get_p1_shoot()[0],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;
                    }

                    renderer.render(player.position,  &player_sprite, 180.0f);
                    break;
                case -1:
                    if(shoot)
                    {

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.normal_sprites.back().w / 2) - y_precision, player.position.y - 15),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[0],
                                CollisionManager::get_player_bullet_collision()

                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.normal_sprites.back().w / 2) - y_precision, player.position.y + player.normal_sprites.back().h),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[0],
                                CollisionManager::get_player_bullet_collision()
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
                                Vector2(player.position.x + player.normal_sprites.back().w - 5, player.position.y),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[3],
                                CollisionManager::get_player_bullet_collision()
                        ));



                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 5,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[3],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;

                    }

                    player_sprite = {
                            player.normal_sprites.back().x,
                            player.normal_sprites.back().y,
                            player.normal_sprites.back().w,
                            player.normal_sprites.back().h

                    };

                    renderer.render(player.position,  &player_sprite, -90.0f);
                    break;
                case 0:

                    if(shoot)
                    {

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x, player.position.y + (player.normal_sprites.back().h / 2) - y_precision ),
                                        player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[2],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w, player.position.y + (player.normal_sprites.back().h / 2) - y_precision ),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[2],
                                CollisionManager::get_player_bullet_collision()
                        ));
                    }


                    player_sprite = {
                            player.normal_sprites.front().x,
                            player.normal_sprites.front().y,
                            player.normal_sprites.front().w,
                            player.normal_sprites.front().h

                    };

                    renderer.render(player.position,  &player_sprite, -90.0f);
                    break;
                case -1:

                    if(shoot)
                    {

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x, player.position.y),
                                player.clamped_direction,
                                SpriteSheet::get_p1_shoot()[1],
                                CollisionManager::get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;


                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction * (-1),
                                SpriteSheet::get_p1_shoot()[1],
                                CollisionManager::get_player_bullet_collision()
                        ));





                    }



                    player_sprite = {
                            player.normal_sprites.back().x,
                            player.normal_sprites.back().y,
                            player.normal_sprites.back().w,
                            player.normal_sprites.back().h

                    };

                    renderer.render(player.position, &player_sprite, 0.0f);
                    break;
            }
            break;

    }

    // TODO: delete
    renderer.render_collision_box(player);
}

void GameHandler::load_sprite_sheet()
{
    SpriteSheetLoader::load_sprite_sheet_surface(renderer, SpriteSheet::PATH_TO_SPRITE_SHEET);

}


void GameHandler::initialize_quad_tree()
{
    quad_tree = QuadTree(
            {
                    (int)level_manager.current_tile_position.x - (int(Level::AMOUNT_OF_TILES_X / 2) * Level::TILE_SIZE_X ),
                    (int)level_manager.current_tile_position.y - (int(Level::AMOUNT_OF_TILES_Y / 2) * Level::TILE_SIZE_Y ),
                Level::LEVEL_SIZE_X,
                Level::LEVEL_SIZE_Y
            });
}

void GameHandler::run() {

    initialize();

    game_loop();

    renderer.clear();

}


void GameHandler::initialize()
{

    load_sprite_sheet();

    renderer.set_scale(scale);
    CollisionManager::scale = scale;
    CollisionManager::create_collision_circles();

    player = Player(SpriteSheet::get_player_sprites(), SpriteSheet::get_explosion_1(), CollisionManager::get_player_collision());

    level_manager.initialize_tile_index(player.position);


    // TODO: testing
    level_manager.spawn_random_enemy();

}

void GameHandler::game_loop()
{
    fps_timer.start();
    while(!quit_game)
    {

        renderer.clear_screen();

        float delta = fps_timer.get_delta();

        // input handling
        bool shoot = false;

        switch (Input::handle_user_input(keyboard_input_vector, frame_counter))
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
        level_manager.set_current_tile(player.position); // rearrange tiles

        initialize_quad_tree();
        quad_tree.insert(player);

        Vector2 player_sprite_size((float)player.normal_sprites.front().w, (float)player.normal_sprites.front().h);
        renderer.update_camera(player.position, player_sprite_size);

        // move bullets
        move_bullets(delta);

        // move enemies
        level_manager.move_enemies(delta, quad_tree);


        // check player collision
        quad_tree.check_collision(player);

        // check bullet collisions
        check_bullet_collisions();

        // check enemy collisions
        level_manager.check_enemy_collisions(quad_tree);

        // render bullets
        render_bullets();

        // render enemies
        level_manager.render_enemies(renderer);

        // render player, create new bullets
        match_player_direction(shoot);




        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }
}
