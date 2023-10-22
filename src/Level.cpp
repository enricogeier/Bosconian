#include "Level.h"

Level::Level(int current_tile_index): current_tile_index(current_tile_index)
{
    for(int i = 0, tile_index = 0; i < AMOUNT_OF_TILES_X; i++)
    {
        for(int j = 0; j < AMOUNT_OF_TILES_Y; j++)
        {
            tiles[tile_index++] = Tile(Vector2(i * TILE_SIZE_X, j * TILE_SIZE_Y));
        }

    }
}

void Level::set_current_tile(Vector2 &player_position)
{
    if(!(tiles[current_tile_index].is_player_within_tile(player_position, Vector2(TILE_SIZE_X, TILE_SIZE_Y))))
    {
        for(int i = 0; i < AMOUNT_OF_TILES_X * AMOUNT_OF_TILES_Y; i++)
        {
            if(i == current_tile_index)
            {
                continue;
            }
            else if(tiles[current_tile_index].is_player_within_tile(player_position, Vector2(TILE_SIZE_X, TILE_SIZE_Y)))
            {
                current_tile_index = i;
                Vector2& tile_position = tiles[current_tile_index].tile_position;
                int n = (int)tile_position.y - TILE_SIZE_Y;
                int s = (int)tile_position.y + TILE_SIZE_Y;
                int w = (int)tile_position.x - TILE_SIZE_X;
                int e = (int)tile_position.x + TILE_SIZE_X;
                check_tile_positions(n, e, s, w);
                break;
            }
        }
    }

    std::cout << current_tile_index << std::endl;
}

void Level::check_tile_positions(int& n, int& e, int& s, int& w) const
{
    for(int i = 0; i < AMOUNT_OF_TILES_X * AMOUNT_OF_TILES_Y; i++)
    {
        if(i == current_tile_index)
        {
            continue;
        }

        Vector2 position = tiles[i].tile_position;
        bool has_changed = false;

        if((int)position.x < w)
        {
            has_changed = true;
            position.x += AMOUNT_OF_TILES_X * TILE_SIZE_X;
        }
        else if((int)position.x > e)
        {
            has_changed = true;
            position.x -= AMOUNT_OF_TILES_X * TILE_SIZE_X;
        }

        if((int)position.y < n)
        {
            has_changed = true;
            position.y += AMOUNT_OF_TILES_Y * TILE_SIZE_Y;
        }
        else if((int)position.y > s)
        {
            has_changed = true;
            position.y -= AMOUNT_OF_TILES_Y * TILE_SIZE_Y;
        }

        if(has_changed)
        {
            tiles[i].update_tile_position();
        }


    }
}