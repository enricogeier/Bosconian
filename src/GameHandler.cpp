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


void GameHandler::move_enemies(std::vector<Enemy>& enemies, float &delta)
{

    for(auto& enemy : enemies)
    {
        if(enemy.collision_circle.layer == Layer::ENEMY)
        {
            Vector2 move_direction(0.0f, 0.0f);
            enemy.move(move_direction, delta);

        }

        quad_tree.insert(enemy);
    }
}

void GameHandler::check_bullet_collisions()
{
    for(auto& bullet: bullet_list)
    {
        quad_tree.check_collision(bullet);
    }
}

void GameHandler::check_enemy_collisions(std::vector<Enemy>& enemies)
{
    for(auto& enemy : enemies)
    {
        quad_tree.check_collision(enemy);
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

void GameHandler::render_enemies(std::vector<Enemy> &enemies)
{
    for(auto& enemy : enemies)
    {
        // testing: always take first sprite of object
        SDL_Rect sprite{
                enemy.normal_sprites[0].x,
                enemy.normal_sprites[0].y,
                enemy.normal_sprites[0].w,
                enemy.normal_sprites[0].h
        };

        // TODO: implement explosion (enum) then remove element from objects


        renderer.render(enemy.position, &sprite);

        // TODO: delete
        renderer.render_collision_box(enemy);
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

void GameHandler::run() {

    initialize();

    game_loop();

    renderer.clear();

}

void GameHandler::spawn_random_enemy()
{
    // TODO: testing
    Enemy enemy = Enemy(
            Vector2(250, 250),
            SpriteSheet::get_e_type(false),
            SpriteSheet::get_explosion_1(),
            CollisionManager::get_e_type_collision()
    );

    level.set_enemy(enemy);
}

void GameHandler::initialize()
{

    load_sprite_sheet();

    renderer.set_scale(scale);
    CollisionManager::scale = scale;
    CollisionManager::create_collision_circles();

    player = Player(SpriteSheet::get_player_sprites(), SpriteSheet::get_explosion_1(), CollisionManager::get_player_collision());

    level.initialize_tile_index(player.position);


    // TODO: testing
    spawn_random_enemy();

}

void GameHandler::game_loop()
{
    fps_timer.start();
    while(!quit_game)
    {

        renderer.clear_screen();

        float delta = fps_timer.get_delta();

        quad_tree = QuadTree({0, 0, level.LEVEL_SIZE_X, level.LEVEL_SIZE_Y});

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
        quad_tree.insert(player);

        level.set_current_tile(player.position); // rearrange tiles
        Vector2 player_sprite_size((float)player.normal_sprites.front().w, (float)player.normal_sprites.front().h);
        renderer.update_camera(player.position, player_sprite_size);

        // move bullets
        move_bullets(delta);

        // move enemies
        std::vector<Enemy> enemies = level.get_all_game_objects();
        move_enemies(enemies, delta);

        // check player collision
        quad_tree.check_collision(player);

        // check bullet collisions
        check_bullet_collisions();

        // check enemy collisions
        check_enemy_collisions(enemies);

        // render bullets
        render_bullets();

        // render enemies
        render_enemies(enemies);




        // render player, create new bullets
        match_player_direction(shoot);




        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }
}
