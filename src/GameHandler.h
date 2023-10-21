#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <SDL.h>
#include "Player.h"
#include "Renderer.h"
#include "Vector2.h"
#include "SpriteSheet.h"
#include "SpriteSheetLoader.h"
#include "Settings.h"
#include "FPSTimer.h"
#include "Input.h"
#include <string>


class GameHandler
{
private:
    Player player;
    Renderer renderer;
    Vector2 keyboard_input_vector;
    bool quit_game;
    std::list<SDL_Rect> player_sprites;
    FPSTimer fps_timer;
    long int frame_counter = 1;
    float previous_screen_scale = 1.0f;
    float screen_scale = 4.0f;


public:
    GameHandler();

    void initialize();

    void game_loop();

    void match_input_vector(Vector2& camera_position);

    void load_sprite_sheet();

    void run();

};






#endif