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
     Vector2 scale = Vector2(4.0f, 4.0f);


    void initialize();

    void game_loop();

    void match_player_direction(bool& shoot);

    void load_sprite_sheet();

    void move_bullets(float& delta);

    void move_enemies(std::vector<Enemy>& enemies, float& delta);

    void check_bullet_collisions();

    void check_enemy_collisions(std::vector<Enemy>& enemies);

    void render_bullets();

    void render_enemies(std::vector<Enemy>& enemies);

    void spawn_random_enemy();




public:

   GameHandler() = default;

   void run();

};






#endif