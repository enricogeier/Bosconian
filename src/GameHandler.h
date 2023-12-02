#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <string>
#include "Player.h"
#include "FPSTimer.h"
#include "Input.h"
#include "Level.h"
#include "Bullet.h"
#include "QuadTree.h"
#include "BulletHandler.h"




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
     BulletHandler bullet_handler;
     Input input;
     QuadTree quad_tree;
     CollisionManager collision_manager;


    void initialize();

    void game_loop();

    void render_bullets();

    void initialize_quad_tree();

    void render_game_objects();



public:

   GameHandler() = default;

   void run();

};


#endif