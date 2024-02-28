#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <random>
#include "Tile.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "Bullet.h"
#include "Level.h"
#include "QuadTree.h"
#include "CollisionManager.h"
#include "Player.h"
#include "FPSTimer.h"

enum LevelState
{
    WAIT,
    RUNNING,
    LOST_LIVE,
    GAME_OVER,
    RESTART,
    FINISHED_LEVEL

};



class Level
{
private:

    const std::string LEVEL_FOLDER_LOCATION = "../Level/";
    const uint8_t AMOUNT_OF_ROUNDS = 3;

    const short OBJECTS_IN_TILE = 8;
    float PLAYER_OBJECT_DISTANCE = 300.0f;
    float PLAYER_CANNON_DISTANCE = 400.0f;

    int start_tile = 0;
    std::chrono::microseconds timer = std::chrono::microseconds(0);
    std::chrono::microseconds lost_life_timer = std::chrono::microseconds(0);
    std::chrono::microseconds enemy_timer = std::chrono::microseconds(0);
    std::chrono::microseconds cannon_timer = std::chrono::microseconds(0);



    Tile tiles[9];
    int current_tile_index = 0;
    QuadTree quad_tree;
    CollisionManager collision_manager;
    BulletHandler bullet_handler;
    Player player;

    FPSTimer fps_timer;
    long frame_counter = 1;
    float delta = 0.0f;

    void initialize_tiles();

    void initialize_tile_index();

    void set_current_tile();

    void check_tile_positions();

    void move_enemies();

    void check_enemy_collisions();

    void load_level();

public:

    Score score;

    uint8_t current_round = 1;

    LevelState state = LevelState::WAIT;

    Vector2 start_position = Vector2();

    const int LEVEL_SIZE_X = 4500;
    const int LEVEL_SIZE_Y = 7800;

    const int TILE_SIZE_X = 1500;
    const int TILE_SIZE_Y = 2600;

    const int AMOUNT_OF_TILES_X = 3;
    const int AMOUNT_OF_TILES_Y = 3;

    Vector2 current_tile_position = Vector2();

    explicit Level();

    void update(Vector2 player_direction = Vector2(0.0f, 0.0f), bool shoot = false, bool accelerate = false);

    [[nodiscard]] std::vector<GameObject> get_all_game_objects() const;

    [[nodiscard]] std::vector<Enemy> get_all_enemies() const;

    [[nodiscard]] std::vector<Mine> get_all_mines() const;

    [[nodiscard]] std::vector<SpaceStation> get_space_stations() const;

    [[nodiscard]] Player get_player() const;

    [[nodiscard]] std::list<Bullet> get_bullets() const;

    [[nodiscard]] const long& get_current_frame() const;


};



#endif
