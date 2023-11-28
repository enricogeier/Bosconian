#include "GameHandler.h"


void GameHandler::move_bullets(float& delta)
{
    for(auto bullet = bullet_list.begin(); bullet != bullet_list.end();)
    {
        float border = 1000.0f;

        if(Vector2::distance(player.position, bullet->position) > border || bullet->state == State::EXPLODE)
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

void GameHandler::render_enemies()
{
    std::vector<Enemy> game_objects = level.get_all_game_objects();
    for(auto& object : game_objects)
    {
        if(object.state == State::NORMAL)
        {
            // TODO: testing: always take first sprite of object
            SDL_Rect sprite{
                    object.normal_sprites[0].x,
                    object.normal_sprites[0].y,
                    object.normal_sprites[0].w,
                    object.normal_sprites[0].h
            };

            renderer.render(object.position, &sprite);

        }
        else
        {

           std::vector<SDL_Rect> explosion_sprites;

           for(int i = 0; i < object.explosion_sprites.size(); i++)
           {
               explosion_sprites.push_back(SDL_Rect{

                       object.explosion_sprites[i].x,
                       object.explosion_sprites[i].y,
                       object.explosion_sprites[i].w,
                       object.explosion_sprites[i].h

               });
           }



            renderer.add_animation(explosion_sprites, frame_counter, object.position);

        }
    }

}

void GameHandler::spawn_random_enemy()
{
    // TODO: testing, implement this!
    std::vector<Rectangle> sprites = renderer.get_asteroid();
    std::vector<Rectangle> explosion_sprites = renderer.get_explosion_1();
    CollisionCircle collision = collision_manager.get_asteroid_collision();

    level.set_enemy(sprites, explosion_sprites, collision);
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
                                renderer.get_p1_shoot()[1],
                                collision_manager.get_player_bullet_collision()
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w + 5,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction,
                                renderer.get_p1_shoot()[1],
                                collision_manager.get_player_bullet_collision()
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
                                renderer.get_p1_shoot()[2],
                                collision_manager.get_player_bullet_collision()
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w,
                                        player.position.y + (player.normal_sprites.back().h / 2) - y_precision),
                                player.clamped_direction,
                                renderer.get_p1_shoot()[2],
                                collision_manager.get_player_bullet_collision()
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
                                renderer.get_p1_shoot()[3],
                                collision_manager.get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 12,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction * (-1),
                                renderer.get_p1_shoot()[3],
                                collision_manager.get_player_bullet_collision()
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
                                renderer.get_p1_shoot()[0],
                                collision_manager.get_player_bullet_collision()
                        ));

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.normal_sprites.back().w / 2) , player.position.y + player.normal_sprites.back().h),
                                Vector2(0, 1),
                                renderer.get_p1_shoot()[0],
                                collision_manager.get_player_bullet_collision()
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
                                renderer.get_p1_shoot()[0],
                                collision_manager.get_player_bullet_collision()

                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + (player.normal_sprites.back().w / 2) - y_precision, player.position.y + player.normal_sprites.back().h),
                                player.clamped_direction * (-1),
                                renderer.get_p1_shoot()[0],
                                collision_manager.get_player_bullet_collision()
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
                                renderer.get_p1_shoot()[3],
                                collision_manager.get_player_bullet_collision()
                        ));



                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x - 5,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction,
                                renderer.get_p1_shoot()[3],
                                collision_manager.get_player_bullet_collision()
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
                                renderer.get_p1_shoot()[2],
                                collision_manager.get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;

                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w, player.position.y + (player.normal_sprites.back().h / 2) - y_precision ),
                                player.clamped_direction * (-1),
                                renderer.get_p1_shoot()[2],
                                collision_manager.get_player_bullet_collision()
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
                                renderer.get_p1_shoot()[1],
                                collision_manager.get_player_bullet_collision()
                        ));

                        bullet_list.back().speed *= 2;


                        bullet_list.push_back(Bullet(
                                Vector2(player.position.x + player.normal_sprites.back().w,
                                        player.position.y + player.normal_sprites.back().h - 1),
                                player.clamped_direction * (-1),
                                renderer.get_p1_shoot()[1],
                                collision_manager.get_player_bullet_collision()
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

}


void GameHandler::initialize_quad_tree()
{
    quad_tree = QuadTree(
            {
                    (int)level.current_tile_position.x - (int(level.AMOUNT_OF_TILES_X / 2) * level.TILE_SIZE_X ),
                    (int)level.current_tile_position.y - (int(level.AMOUNT_OF_TILES_Y / 2) * level.TILE_SIZE_Y ),
                    level.LEVEL_SIZE_X,
                    level.LEVEL_SIZE_Y
            });
}

void GameHandler::player_explode_animation()
{
    // TODO: implement this!

    player.state = State::DESTROY;
}


void GameHandler::run() {

    initialize();

    game_loop();

}


void GameHandler::initialize()
{

    scale = renderer.scale;

    collision_manager = CollisionManager(scale);

    player = Player(renderer.get_player_sprites(), renderer.get_explosion_1(), collision_manager.get_player_collision());

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

        // input handling
        bool shoot = false;

        if(player.state == State::NORMAL)
        {


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
            level.set_current_tile(player.position); // rearrange tiles
            initialize_quad_tree();
            quad_tree.insert(player);

            Vector2 player_sprite_size((float)player.normal_sprites.front().w, (float)player.normal_sprites.front().h);
            renderer.update_camera(player.position, player_sprite_size);
        }


        // move bullets
        move_bullets(delta);

        // move enemies
        level.move_enemies(delta, quad_tree);


        // check player collision
        quad_tree.check_collision(player);

        // check bullet collisions
        check_bullet_collisions();

        // check enemy collisions
        level.check_enemy_collisions(quad_tree);

        // render animations
        renderer.render_animations(frame_counter);

        // render enemies
        render_enemies();

        // render bullets
        render_bullets();


        // render player, create new bullets
        switch (player.state)
        {
            case State::NORMAL:
                match_player_direction(shoot);
                break;
            case State::EXPLODE:
                player.state = State::DESTROY;
                break;
            case State::DESTROY:
                // TODO: reload level, ...

                break;
        }


        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }

    renderer.clear();
}
