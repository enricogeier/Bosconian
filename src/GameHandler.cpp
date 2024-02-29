#include "GameHandler.h"


void GameHandler::run() {

    bool quit_game = false;
    renderer.set_level(&level);

    while(!quit_game)
    {

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
                case MOVE_PRESSED:
                    accelerate = true;

            }

            level.update(keyboard_input_vector, shoot, accelerate);

        }
        else
        {
            keyboard_input_vector = Vector2();

            level.update();

            switch(input.handle_user_destroyed_input())
            {
                case NONE:
                    break;
                case CLOSE_WINDOW:
                    quit_game = true;
            }
        }


        renderer.update();


    }

    renderer.clear();
    level.sound.close();

}

