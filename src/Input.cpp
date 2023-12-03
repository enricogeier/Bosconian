#include "Input.h"


bool Input::is_key_pressed(SDL_KeyCode key)
{
    if(actually_released.find(key) == actually_released.end())
    {
        return true;
    }
    else
    {
        return false;
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


 InputState Input::handle_user_input(Vector2& keyboard_input_vector, long int& current_frame)
 {
    // Handle events on queue. SDL's internal keystates are updated every time SDL PollEvent is called

    Vector2 initial_input_vector = keyboard_input_vector;
    InputState return_value = NONE;

    while (SDL_PollEvent(&event))
    {

        // User requests quit
        if (event.type == SDL_QUIT)
        {
            return CLOSE_WINDOW;

        }
        else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {

            switch (event.key.keysym.sym)
            {
                case SDLK_SPACE:
                    if(current_frame - last_frame_shoot_pressed > TIME_BETWEEN_SHOTS)
                    {
                        last_frame_shoot_pressed = current_frame;
                        return SHOOT_PRESSED;
                    }
                    else
                    {
                        break;
                    }

                case SDLK_UP:
                    actually_released.erase(SDLK_UP);
                    keyboard_input_vector.y = -1.0f;
                    key_pressed[SDLK_UP] = current_frame;
                    if(actually_released.size() == 3)
                    {
                        keyboard_input_vector.x = 0.0f;
                    }

                    break;

                case SDLK_DOWN:
                    actually_released.erase(SDLK_DOWN);
                    keyboard_input_vector.y = 1.0f;
                    key_pressed[SDLK_DOWN] = current_frame;
                    if(actually_released.size() == 3)
                    {
                        keyboard_input_vector.x = 0.0f;
                    }

                    break;

                case SDLK_LEFT:
                    actually_released.erase(SDLK_LEFT);
                    keyboard_input_vector.x = -1.0f;
                    key_pressed[SDLK_LEFT] = current_frame;
                    if(actually_released.size() == 3)
                    {
                        keyboard_input_vector.y = 0.0f;
                    }

                    break;

                case SDLK_RIGHT:
                    actually_released.erase(SDLK_RIGHT);
                    keyboard_input_vector.x = 1.0f;
                    key_pressed[SDLK_RIGHT] = current_frame;
                    if(actually_released.size() == 3)
                    {
                        keyboard_input_vector.y = 0.0f;
                    }

                    break;


            }

            if(!first_move_key_pressed && keyboard_input_vector != initial_input_vector)
            {
                first_move_key_pressed = true;
                return_value = FIRST_MOVE_PRESSED;
            }

        }
        else if (event.type == SDL_KEYUP && event.key.repeat == 0)
        {
            if(event.key.keysym.sym == SDLK_UP)
            {
                actually_released.insert(SDLK_UP);
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
                        if(!(is_key_pressed(SDLK_LEFT) || is_key_pressed(SDLK_RIGHT)))
                        {
                            keyboard_input_vector.x = 0.0f;
                        }

                }
            }
            else if(event.key.keysym.sym == SDLK_DOWN)
            {
                actually_released.insert(SDLK_DOWN);
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
                        if(!(is_key_pressed(SDLK_LEFT) || is_key_pressed(SDLK_RIGHT)))
                        {
                            keyboard_input_vector.x = 0.0f;
                        }
                }
            }
            else if(event.key.keysym.sym == SDLK_LEFT)
            {
                actually_released.insert(SDLK_LEFT);
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
                        if(!(is_key_pressed(SDLK_UP) || is_key_pressed(SDLK_DOWN)))
                        {
                            keyboard_input_vector.y = 0.0f;
                        }
                }
            }
            else if(event.key.keysym.sym == SDLK_RIGHT)
            {
                actually_released.insert(SDLK_RIGHT);
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
                        if(!(is_key_pressed(SDLK_UP) || is_key_pressed(SDLK_DOWN)))
                        {
                            keyboard_input_vector.y = 0.0f;
                        }
                }
            }

        }
    }

    return return_value;
}

InputState Input::handle_user_destroyed_input()
{
    while(SDL_PollEvent(&event))
    {
        // User requests quit
        if (event.type == SDL_QUIT)
        {
            return CLOSE_WINDOW;

        }
    }

    return NONE;
}
