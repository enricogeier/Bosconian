#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <list>
#include "Tile.h"
#include "Enemy.h"
#include "SpriteSheet.h"
#include "CollisionManager.h"
#include "Level.h"


class LevelManager
{
private:

    Tile tiles[9];
    int current_tile_index = 0;

public:

    Vector2 current_tile_position = Vector2();

    explicit LevelManager();

    void initialize_tile_index(Vector2& player_position);

    void set_current_tile(Vector2& player_position);

    void check_tile_positions();

    void spawn_random_enemy();

    void move_enemies(float& delta);

    std::vector<Enemy> get_all_game_objects() const;


};



#endif
