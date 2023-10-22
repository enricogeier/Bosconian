#include "Level.h"

Level::Level()
{
    for(int i = 0, tile_index = 0; i < AMOUNT_OF_TILES_X; i++)
    {
        for(int j = 0; j < AMOUNT_OF_TILES_Y; j++)
        {
            tiles[tile_index++] = Tile(Vector2(i * TILE_SIZE_X, j * TILE_SIZE_Y));
        }

    }
}

void Level::check_tile_positions()
{

}