#include "Input.h"

void Input::disable_active_keys(Vector2 &keyboard_input)
{
    for(auto key : still_active)
    {
        if(key == SDLK_UP || key == SDLK_DOWN)
        {
            keyboard_input.y = 0.0f;
        }
        else if(key == SDLK_LEFT || key == SDLK_RIGHT)
        {
            keyboard_input.x = 0.0f;
        }
    }
}

SDL_KeyCode Input::find_entry(std::map<SDL_KeyCode, long>& key_map, SDL_KeyCode key_code, long int& frame_number)
{
    for(auto const& [key, frame] : key_map)
    {
        if((((frame_number - frame) < 3 && (frame_number - frame) >= 0) || ((frame - frame_number) < 3 && (frame - frame_number) >= 0)) && key != key_code)
        {
            return key;
        }
    }
}


 bool Input::handle_user_input(Vector2& keyboard_input_vector, long int& current_frame)
 {
    // Handle events on queue. SDL's internal keystates are updated every time SDL PollEvent is called
    while (SDL_PollEvent(&event))
    {

        // User requests quit
        if (event.type == SDL_QUIT)
        {
            return true;

        }
        else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {

            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    disable_active_keys(keyboard_input_vector);
                    keyboard_input_vector.y = -1.0f;
                    key_pressed[SDLK_UP] = current_frame;
                    std::cout << current_frame << std::endl;
                    break;

                case SDLK_DOWN:
                    disable_active_keys(keyboard_input_vector);
                    keyboard_input_vector.y = 1.0f;
                    key_pressed[SDLK_DOWN] = current_frame;
                    std::cout << current_frame << std::endl;
                    break;

                case SDLK_LEFT:
                    disable_active_keys(keyboard_input_vector);
                    keyboard_input_vector.x = -1.0f;
                    key_pressed[SDLK_LEFT] = current_frame;
                    std::cout << current_frame << std::endl;
                    break;

                case SDLK_RIGHT:
                    disable_active_keys(keyboard_input_vector);
                    keyboard_input_vector.x = 1.0f;
                    key_pressed[SDLK_RIGHT] = current_frame;
                    std::cout << current_frame << std::endl;
                    break;


            }


        }
        else if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            if(event.key.keysym.sym == SDLK_UP)
            {
                std::cerr << current_frame << std::endl;
                key_released[SDLK_UP] = current_frame;

                SDL_KeyCode key = find_entry(key_released, SDLK_UP, current_frame);

                switch(key)
                {
                    case SDLK_DOWN:
                        keyboard_input_vector.y = 0.0f;
                        break;

                    case SDLK_LEFT:
                        keyboard_input_vector.x = -1.0f;
                        still_active.insert(SDLK_LEFT);
                        break;

                    case SDLK_RIGHT:
                        keyboard_input_vector.x = 1.0f;
                        still_active.insert(SDLK_RIGHT);
                        break;

                    default:
                        keyboard_input_vector.y = 0.0f;
                }
            }
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                std::cerr << current_frame << std::endl;
                key_released[SDLK_DOWN] = current_frame;

                SDL_KeyCode key = find_entry(key_released, SDLK_DOWN, current_frame);

                switch(key)
                {
                    case SDLK_UP:
                        keyboard_input_vector.y = 0.0f;
                        break;

                    case SDLK_LEFT:
                        keyboard_input_vector.x = -1.0f;
                        still_active.insert(SDLK_LEFT);
                        break;

                    case SDLK_RIGHT:
                        keyboard_input_vector.x = 1.0f;
                        still_active.insert(SDLK_RIGHT);
                        break;

                    default:
                        keyboard_input_vector.y = 0.0f;
                }
            }
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                std::cerr << current_frame << std::endl;
                key_released[SDLK_LEFT] = current_frame;

                SDL_KeyCode key = find_entry(key_released, SDLK_LEFT, current_frame);

                switch(key)
                {
                    case SDLK_UP:
                        keyboard_input_vector.y = -1.0f;
                        still_active.insert(SDLK_UP);
                        break;

                    case SDLK_DOWN:
                        keyboard_input_vector.y = 1.0f;
                        still_active.insert(SDLK_DOWN);
                        break;

                    case SDLK_RIGHT:
                        keyboard_input_vector.x = 0.0f;
                        break;

                    default:
                        keyboard_input_vector.x = 0.0f;
                }
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                std::cerr << current_frame << std::endl;
                key_released[SDLK_RIGHT] = current_frame;

                SDL_KeyCode key = find_entry(key_released, SDLK_RIGHT, current_frame);

                switch(key)
                {
                    case SDLK_UP:
                        keyboard_input_vector.y = -1.0f;
                        still_active.insert(SDLK_UP);
                        break;

                    case SDLK_DOWN:
                        keyboard_input_vector.y = 1.0f;
                        still_active.insert(SDLK_DOWN);
                        break;

                    case SDLK_LEFT:
                        keyboard_input_vector.x = 0.0f;
                        break;

                    default:
                        keyboard_input_vector.x = 0.0f;
                }
            }

        }
    }

    return false;
}