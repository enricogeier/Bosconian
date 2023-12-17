#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <list>
#include "Tile.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "Bullet.h"
#include "Level.h"
#include "QuadTree.h"
#include "CollisionManager.h"
#include "Player.h"



class Level
{
private:

    Tile tiles[9];
    int current_tile_index = 0;
    QuadTree quad_tree;
    CollisionManager collision_manager;
    BulletHandler bullet_handler;
    Player player;

    void initialize_tile_index();

    void set_current_tile();

    void check_tile_positions();

    void set_enemy();

    void move_enemies(float& delta);

    void check_enemy_collisions();


public:

    const int LEVEL_SIZE_X = 4500;
    const int LEVEL_SIZE_Y = 7800;

    const int TILE_SIZE_X = 1500; // default: 2000
    const int TILE_SIZE_Y = 2600; // default: 2667
    const int AMOUNT_OF_TILES_X = 3;
    const int AMOUNT_OF_TILES_Y = 3;

    Vector2 current_tile_position = Vector2();

    explicit Level();

    void initialize_quad_tree();

    void update_player(Vector2& player_direction, float& delta, bool& shoot, bool& accelerate);

    void handle_player_state();

    void update(float& delta);

    [[nodiscard]] std::vector<GameObject> get_all_game_objects() const;

    [[nodiscard]] std::vector<Enemy> get_all_enemies() const;

    [[nodiscard]] std::vector<Mine> get_all_mines() const;

    [[nodiscard]] std::vector<SpaceStation> get_space_stations() const;

    [[nodiscard]] Player get_player() const;

    std::list<Bullet> get_bullets();


};



#endif
