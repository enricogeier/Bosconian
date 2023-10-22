#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "Tile.h"


class Level
{
private:
    Tile tiles[8];
    int& current_tile_index;

public:
    const int LEVEL_SIZE_X = 6000;
    const int LEVEL_SIZE_Y = 8000;

    inline static const int TILE_SIZE_X = 2; // default: 2000
    inline static const int TILE_SIZE_Y = 2; // default: 2667
    inline static const int AMOUNT_OF_TILES_X = 3;
    inline static const int AMOUNT_OF_TILES_Y = 3;

    explicit Level();

    void check_tile_positions();


};



#endif
