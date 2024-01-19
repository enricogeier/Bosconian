#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include "Vector2.h"
#include "Renderer.h"

enum InputState
{
    NONE,
    SHOOT_PRESSED,
    MOVE_PRESSED,
    CLOSE_WINDOW
};


class Input
{
private:
    SDL_Event event;
    std::map<SDL_KeyCode, long int> key_pressed  = {{SDLK_UP, -1000}, {SDLK_DOWN, -1000}, {SDLK_LEFT, -1000}, {SDLK_RIGHT, -1000}};;
    std::map<SDL_KeyCode, long int> key_released = {{SDLK_UP, -1000}, {SDLK_DOWN, -1000}, {SDLK_LEFT, -1000}, {SDLK_RIGHT, -1000}};;
    std::set<SDL_KeyCode> still_active;
    std::set<SDL_KeyCode> actually_released = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT};;

    bool is_key_pressed(SDL_KeyCode key);
    SDL_KeyCode find_entry(std::map<SDL_KeyCode, long int>& key_map, SDL_KeyCode key_code, long int& frame_number);

    long last_frame_shoot_pressed = -99;

    const int TIME_BETWEEN_SHOTS = 8;


public:
    Input() = default;

    InputState handle_user_input(Vector2& keyboard_input_vector, long int& current_frame);

    InputState handle_user_destroyed_input();



};



#endif
