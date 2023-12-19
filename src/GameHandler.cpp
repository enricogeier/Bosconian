#include "GameHandler.h"


void GameHandler::render()
{
    renderer.render_side_bar();

    renderer.render_animations();

    std::vector<GameObject> asteroids = level.get_all_game_objects();

    for(auto& asteroid : asteroids)
    {
        renderer.render_asteroid(asteroid);
    }

    std::vector<Mine> mines = level.get_all_mines();

    for(auto& mine : mines)
    {
        renderer.render_mine(mine);
    }

    std::vector<Enemy> enemies = level.get_all_enemies();

    for(auto& enemy : enemies)
    {
        switch (enemy.type)
        {
            case E_TYPE:
                renderer.render_e_type(enemy);
                break;
            case P_TYPE:
                renderer.render_p_type(enemy);
                break;
            case I_TYPE:
                renderer.render_i_type(enemy);
                break;
            case SPY:
                renderer.render_spy(enemy);
                break;
        }
    }

    std::vector<SpaceStation> stations = level.get_space_stations();
    for(auto& station : stations)
    {
        renderer.render_space_station(station);

        // TODO: TESTING, DELETE THIS!
        //renderer.render_collision_box(station);

        for(auto& cannon : station.cannons)
        {
            //renderer.render_collision_box(cannon);
        }


    }

    std::list<Bullet> bullet_list = level.get_bullets();
    for(auto& bullet : bullet_list)
    {
        renderer.render_bullet(bullet);

        //TODO: testing, delete this!

        //renderer.render_collision_box(bullet);
    }

    renderer.render_player(level.get_player());

    //TODO: testing, delete this!
    //renderer.render_collision_box(level.get_player());




    renderer.update_screen();
}


void GameHandler::run() {

    fps_timer.start();
    while(!quit_game)
    {

        renderer.clear_screen();

        float delta = fps_timer.get_delta();

        level.initialize_quad_tree();

        if(level.get_player().state == State::NORMAL)
        {
            bool shoot = false;
            bool accelerate = false;

            switch (input.handle_user_input(keyboard_input_vector, frame_counter))
            {
                case NONE:
                    break;
                case SHOOT_PRESSED:
                    shoot = true;
                    break;
                case CLOSE_WINDOW:
                    quit_game = true;
                    break;
                case FIRST_MOVE_PRESSED:
                    accelerate = true;

            }

            level.update_player(keyboard_input_vector, delta, shoot, accelerate);

            renderer.update_camera(level.get_player().position);

        }
        else
        {
            level.handle_player_state();

            switch(input.handle_user_destroyed_input())
            {
                case NONE:
                    break;
                case CLOSE_WINDOW:
                    quit_game = true;
            }
        }


       level.update(delta);

        render();



        fps_timer.clamp_and_print_fps(frame_counter);
        frame_counter++;

    }

    renderer.clear();

}

