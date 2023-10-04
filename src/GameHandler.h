#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <SDL.h>
#include "Player.h"
#include "Renderer.h"
#include "Vector2.h"
#include "SpriteSheet.h"
#include "SpriteSheetLoader.h"


class GameHandler
{
private:
    Player player;
    Renderer renderer;
    Vector2 keyboard_input_vector;
    bool quit_game;
    std::list<SDL_Rect> player_sprites;


public:
    GameHandler();

    void initialize();

    void game_loop();

    void match_input_vector();

    void load_sprite_sheet();

    void handle_input();

    void run();

};






#endif