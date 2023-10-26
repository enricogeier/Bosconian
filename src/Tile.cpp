#include "Tile.h"

Tile::Tile(Vector2 position) : tile_position(position)
{
}


bool Tile::is_player_within_tile(Vector2 &player_position, Vector2 tile_size) const
{

    Vector2 test = tile_position;


    if(
            (int)player_position.x <= (int)tile_position.x + (int)tile_size.x && (int)player_position.x >= (int)tile_position.x
            && (int)player_position.y <= (int)tile_position.y + (int)tile_size.y && (int)player_position.y >= (int)tile_position.y
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Tile::update_tile_position() const
{
    // update everything's position






}