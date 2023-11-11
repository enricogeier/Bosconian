#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <string>
#include "Player.h"
#include "Renderer.h"
#include "SpriteSheetLoader.h"
#include "FPSTimer.h"
#include "Input.h"
#include "Level.h"
#include "Bullet.h"
#include "QuadTree.h"


class GameHandler
{
private:
     Player player;
     Renderer renderer;
     Vector2 keyboard_input_vector;
     bool quit_game = false;
     FPSTimer fps_timer;
     long frame_counter = 1;
     Level level;
     std::list<Bullet> bullet_list;
     QuadTree quad_tree;


    void initialize();

    void game_loop();

    void match_player_direction(bool& shoot);

    void load_sprite_sheet();




public:

   GameHandler() = default;

   void run();

};






#endif