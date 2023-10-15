#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include "Vector2.h"

class Input
{
private:
    inline static SDL_Event event;
    inline static std::map<SDL_KeyCode, long int> key_pressed = {{SDLK_UP, -1000}, {SDLK_DOWN, -1000}, {SDLK_LEFT, -1000}, {SDLK_RIGHT, -1000}};
    inline static std::map<SDL_KeyCode, long int> key_released= {{SDLK_UP, -1000}, {SDLK_DOWN, -1000}, {SDLK_LEFT, -1000}, {SDLK_RIGHT, -1000}};
    inline static std::set<SDL_KeyCode> still_active;
    inline static std::set<SDL_KeyCode> actually_released;

    static bool is_key_pressed(SDL_KeyCode key);
    static void disable_active_keys(Vector2& keyboard_input, SDL_KeyCode ignore_key);
    static SDL_KeyCode find_entry(std::map<SDL_KeyCode, long int>& key_map, SDL_KeyCode key_code, long int& frame_number);


public:
    static bool handle_user_input(Vector2& keyboard_input_vector, long int& current_frame);


};



#endif
