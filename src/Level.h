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
#include "Sound.h"

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

    /**
     * Initializes tile positions.
     */
    void initialize_tiles();

    /**
     * Sets the current tile and update other tiles.
     */
    void initialize_tile_index();

    /**
     * Changes the current tile and update other tiles.
     */
    void set_current_tile();

    /**
     * Check if tile position should be changed. If true function calls update_tile_positions() of a Tile object.
     */
    void check_tile_positions();

    /**
     * Spawns and moves enemies.
     */
    void move_enemies();

    /**
     * Checks enemy collsions. Calls check_collision function of the QuadTree object.
     */
    void check_enemy_collisions();

    /**
     * Load a specific Level based on current_round attribute.
     */
    void load_level();

    /**
     * Clears level. Removes anything in the game except the player.
     */
    void clear();

public:

    Sound sound;

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

    /**
     * Constructs a new Level object. Represents the model.
     */
    explicit Level();

    /**
     * Updates the game logic within a frame.
     *
     * @param player_direction user keyboard input within current frame. Default value is (0.0f, 0.0f) if not provided.
     * @param shoot true if shoot was pressed, false otherwise. Default value is false if not provided.
     * @param accelerate true if first user input while level start. false otherwise. Default value is false if not provided.
     */
    void update(Vector2 player_direction = Vector2(0.0f, 0.0f), bool shoot = false, bool accelerate = false);

    /**
     * Retrieves all asteroids currently used in game.
     *
     * @return list of game objects currently used in game.
     */
    std::vector<GameObject> get_all_game_objects() const;

    /**
     * Retrieves all enemies currently used in game.
     *
     * @return list of enemies currently used in game.
     */
    std::vector<Enemy> get_all_enemies() const;

    /**
     * Retrieves all mines currently used in game.
     *
     * @return list of mines currently used in game.
     */
    std::vector<Mine> get_all_mines() const;

    /**
     * Retrieves all space stations and its cannons used in game.
     *
     * @return list of space stations used in game.
     */
    std::vector<SpaceStation> get_space_stations() const;

    /**
     * Retrieves the Player instance.
     *
     * @return the Player instance.
     */
    Player get_player() const;


    /**
     * Retrieves all bullets currently used in game.
     *
     * @return list of all bullets currently used in game.
     */
    std::list<Bullet> get_bullets() const;

    /**
     * Retrieves the current frame number.
     *
     * @return Reference of the current frame number.
     */
    const long& get_current_frame() const;


};



#endif
