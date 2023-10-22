#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "Tile.h"


class Level
{
private:
    inline static Tile tiles[8];
    int current_tile_index;

public:
    const int LEVEL_SIZE_X = 6000;
    const int LEVEL_SIZE_Y = 8000;

    inline static const int TILE_SIZE_X = 2000; // default: 2000
    inline static const int TILE_SIZE_Y = 2667; // default: 2667
    inline static const int AMOUNT_OF_TILES_X = 3;
    inline static const int AMOUNT_OF_TILES_Y = 3;

    explicit Level(int current_tile_index = 0);

    void set_current_tile(Vector2& player_position);

    void check_tile_positions(int& n, int& e, int& s, int& w) const;


};



#endif
