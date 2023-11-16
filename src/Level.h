#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <list>
#include "Tile.h"
#include "Enemy.h"
#include "SpriteSheet.h"
#include "CollisionManager.h"


class Level
{
private:

    Tile tiles[9];
    int current_tile_index = 0;

public:
    const int LEVEL_SIZE_X = 6000;
    const int LEVEL_SIZE_Y = 8000;

    const int TILE_SIZE_X = 2000; // default: 2000
    const int TILE_SIZE_Y = 2667; // default: 2667
    const int AMOUNT_OF_TILES_X = 3;
    const int AMOUNT_OF_TILES_Y = 3;

    explicit Level();

    void initialize_tile_index(Vector2& player_position);

    void set_current_tile(Vector2& player_position);

    void check_tile_positions();

    void set_enemy(Enemy& enemy);

    std::vector<Enemy> get_all_game_objects() const;


};



#endif
