#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <SDL.h>
#include <string>
#include "Player.h"
#include "Renderer.h"
#include "SpriteSheet.h"
#include "SpriteSheetLoader.h"
#include "FPSTimer.h"
#include "Input.h"
#include "Level.h"
#include "Vector4.h"
#include "Rectangle.h"
#include "InputState.h"
#include "Bullet.h"


class GameHandler
{
private:
    Player player;
    Renderer renderer;
    Vector2 keyboard_input_vector;
    bool quit_game = false;
    FPSTimer fps_timer;
    long int frame_counter = 1;
    Level level;

    std::list<Bullet> bullet_list;


public:
    GameHandler() = default;

    void initialize();

    void game_loop();

    void match_player_direction(bool& shoot);

    void load_sprite_sheet();

    void run();

};






#endif