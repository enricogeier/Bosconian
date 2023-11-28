#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <string>
#include "Player.h"
#include "FPSTimer.h"
#include "Input.h"
#include "Level.h"
#include "Bullet.h"
#include "QuadTree.h"
#include "CollisionManager.h"



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
     std::list<AnimationPlayer> animation_list;
     QuadTree quad_tree;
     CollisionManager collision_manager;
     Vector2 scale;


    void initialize();

    void game_loop();

    void match_player_direction(bool& shoot);

    void move_bullets(float& delta);

    void check_bullet_collisions();

    void render_bullets();

    void initialize_quad_tree();

    void render_enemies();

    void spawn_random_enemy();

    void player_explode_animation();



public:

   GameHandler() = default;

   void run();

};






#endif