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

    /**
     * Retrieves information whether key is pressed or not.
     * @param key The key value to check.
     * @return true if key is pressed, false otherwise.
     */
    bool is_key_pressed(SDL_KeyCode key);

    /**
     * Looks for a valid entry in the key map based on the current frame.
     *
     * @param key_map List of keys.
     * @param key_code Value to find in the key map.
     * @param frame_number Current frame number.
     * @return key if value is valid, otherwise nullptr
     */
    SDL_KeyCode find_entry(std::map<SDL_KeyCode, long int>& key_map, SDL_KeyCode key_code, long int& frame_number);

    long last_frame_shoot_pressed = -99;

    const int TIME_BETWEEN_SHOTS = 8;


public:

    /**
     * Constructs a new Input object. Responsible for user input processing.
     */
    Input() = default;

    /**
     * Retrieves user keyboard input for processing.
     *
     * @param keyboard_input_vector Reference to the user input value of the previous frame.
     * @param current_frame Reference to the current frame number.
     * @return
     *         SHOOT_PRESSED: if player pressed shoot (space)
     *         MOVE_PRESSED: if player pressed move
     *         CLOSE_WINDOW: if user closes window
     *         NONE: otherwise
     */
    InputState handle_user_input(Vector2& keyboard_input_vector, long int& current_frame);

    /**
     * Requests information about whether user wants to close the window.
     *
     * @return CLOSE_WINDOW: user closes the window.
     *          NONE: otherwise.
     */
    InputState handle_user_destroyed_input();



};



#endif
