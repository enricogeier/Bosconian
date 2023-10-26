#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "Tile.h"


class Level
{
private:

    Tile tiles[9];
    int current_tile_index = 0;

public:
    const int LEVEL_SIZE_X = 6000;
    const int LEVEL_SIZE_Y = 8000;

    static const int TILE_SIZE_X = 2000; // default: 2000
    static const int TILE_SIZE_Y = 2667; // default: 2667
    static const int AMOUNT_OF_TILES_X = 3;
    static const int AMOUNT_OF_TILES_Y = 3;

    explicit Level();

    void set_current_tile(Vector2& player_position);

    void check_tile_positions(int& n, int& e, int& s, int& w) const;


};



#endif
