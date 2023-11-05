#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include "Vector2.h"
#include "Renderer.h"
#include "InputState.h"

class Input
{
private:
    static SDL_Event event;
    static std::map<SDL_KeyCode, long int> key_pressed;
    static std::map<SDL_KeyCode, long int> key_released;
    static std::set<SDL_KeyCode> still_active;
    static std::set<SDL_KeyCode> actually_released;

    static bool is_key_pressed(SDL_KeyCode key);
    static SDL_KeyCode find_entry(std::map<SDL_KeyCode, long int>& key_map, SDL_KeyCode key_code, long int& frame_number);

    static long last_frame_shoot_pressed;

    static const int TIME_BETWEEN_SHOTS = 8;

public:
    static InputState handle_user_input(Vector2& keyboard_input_vector, long int& current_frame);


};



#endif
