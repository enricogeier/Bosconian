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
        renderer.render_enemy(enemy);
    }

    std::vector<SpaceStation> stations = level.get_space_stations();
    for(auto& station : stations)
    {
        renderer.render_space_station(station);
    }

    std::list<Bullet> bullet_list = level.get_bullets();
    for(auto& bullet : bullet_list)
    {
        renderer.render_bullet(bullet);
    }

    renderer.render_player(level.get_player());



    renderer.update_screen();
}


void GameHandler::run() {

    bool quit_game = false;
    while(!quit_game)
    {

        renderer.clear_screen();

        if(level.get_player().state == State::NORMAL)
        {
            bool shoot = false;
            bool accelerate = false;


            switch (input.handle_user_input(keyboard_input_vector, const_cast<long &>(level.get_current_frame())))
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

            level.update(keyboard_input_vector, shoot, accelerate);

            renderer.update_camera(level.get_player().position);

        }
        else
        {
            level.update();

            switch(input.handle_user_destroyed_input())
            {
                case NONE:
                    break;
                case CLOSE_WINDOW:
                    quit_game = true;
            }
        }


        render();


    }

    renderer.clear();

}

