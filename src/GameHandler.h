#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <SDL.h>
#include "Player.h"
#include "Renderer.h"
#include "Vector2.h"
#include "SpriteSheet.h"
#include "SpriteSheetLoader.h"
#include "FPSTimer.h"
#include "Input.h"
#include "Level.h"
#include <string>


class GameHandler
{
private:
    Player player;
    Renderer renderer;
    Vector2 keyboard_input_vector;
    bool quit_game = false;
    std::list<SDL_Rect> player_sprites;
    FPSTimer fps_timer;
    long int frame_counter = 1;
    Level level;


public:
    GameHandler() = default;

    void initialize();

    void game_loop();

    void match_input_vector();

    void load_sprite_sheet();

    void run();

};






#endif