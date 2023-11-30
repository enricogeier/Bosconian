#include "GameHandler.h"


void GameHandler::render_bullets()
{
    std::list<Bullet> bullet_list = bullet_handler.get_bullets();
    for(auto& bullet : bullet_list)
    {
        renderer.render_bullet(bullet.position, bullet.direction);
    }
}

void GameHandler::render_game_objects()
{
    std::vector<Enemy> enemies = level.get_all_enemies();
    for(auto& enemy : enemies)
    {
            switch (enemy.type)
            {
                case Type::E_TYPE:
                    renderer.render_e_type(enemy);
                    break;
                case Type::P_TYPE:
                    renderer.render_p_type(enemy);
                    break;
                case Type::I_TYPE:
                    renderer.render_i_type(enemy);
                    break;
                case Type::SPY:
                    renderer.render_spy(enemy);
                    break;
            }


    }

    std::vector<CelestialObject> objects = level.get_all_game_objects();
    for(auto& object : objects)
    {
        switch(object.type)
        {
            case CelestialType::ASTEROID:
                renderer.render_asteroid(object);
                break;
            case CelestialType::MINE:
                renderer.render_mine(object);
                break;
        }
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


void GameHandler::run() {

    initialize();

    game_loop();

}


void GameHandler::initialize()
{

    renderer.set_scale(scale);

    collision_manager = CollisionManager(scale);

    player = Player(collision_manager.get_player_collision());

    level.initialize_tile_index(player.position);


    // TODO: testing, delete this!
    level.set_enemy(collision_manager);

}

void GameHandler::game_loop()
{
    fps_timer.start();
    while(!quit_game)
    {

        renderer.clear_screen();

        float delta = fps_timer.get_delta();
        initialize_quad_tree();

        if(player.state == State::NORMAL)
        {
            bool shoot = false;

            switch (input.handle_user_input(keyboard_input_vector, frame_counter))
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
            quad_tree.insert(player);

            renderer.update_camera(player.position);

            if(shoot)
            {
                bullet_handler.insert_player_bullets(player.position,
                                                     player.direction,
                                                     player.clamped_direction,
                                                     collision_manager.get_player_bullet_collision()
                                                     );
            }

        }
        else
        {
            if(player.state == State::EXPLODE)
            {
                player.state = State::DESTROY;
            }

            switch(input.handle_user_destroyed_input())
            {
                case NONE:
                    break;
                case CLOSE_WINDOW:
                    quit_game = true;
                case SHOOT_PRESSED:
                    break;
            }
        }


        // move bullets
        bullet_handler.move_player_bullet(player.position, player.clamped_direction, quad_tree, delta);

        // move enemies
        level.move_enemies(delta, quad_tree);

        // check player collision
        if(player.state == State::NORMAL)
        {
            quad_tree.check_collision(player);
        }

        // check bullet collisions
        bullet_handler.check_collisions(quad_tree);

        // check object collisions
        level.check_enemy_collisions(quad_tree);

        // render animations
        renderer.render_animations();

        // render game objects
        render_game_objects();

        // render bullets
        render_bullets();

        // render player
        renderer.render_player(player);

        renderer.update_screen();
        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }

    renderer.clear();
}
