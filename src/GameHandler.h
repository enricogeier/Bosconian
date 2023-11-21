#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <string>
#include "Player.h"
#include "SpriteSheetLoader.h"
#include "FPSTimer.h"
#include "Input.h"
#include "LevelManager.h"
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
     LevelManager level_manager;
     std::list<Bullet> bullet_list;
     QuadTree quad_tree;
     Vector2 scale = Vector2(4.0f, 4.0f);


    void initialize();

    void game_loop();

    void match_player_direction(bool& shoot);

    void load_sprite_sheet();

    void move_bullets(float& delta);

    void check_bullet_collisions();

    void render_bullets();

    void initialize_quad_tree();



public:

   GameHandler() = default;

   void run();

};






#endif