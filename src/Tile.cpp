#include "Tile.h"

Tile::Tile(Vector2 position) : tile_position(position), last_tile_position(position)
{
}


bool Tile::is_player_within_tile(Vector2 &player_position, Vector2 tile_size) const
{

    if(
            (int)player_position.x < (int)tile_position.x + (int)tile_size.x && (int)player_position.x >= (int)tile_position.x
            && (int)player_position.y < (int)tile_position.y + (int)tile_size.y && (int)player_position.y >= (int)tile_position.y
    )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Tile::update_tile_position()
{
    // update every GameObject position

    Vector2 offset = tile_position - last_tile_position;

    for(auto & object : objects)
    {
        object.position = object.position + offset;
        object.collision_circle.origin = object.position + object.collision_circle.initial_origin;
    }
    for(auto& mine : mines)
    {
        mine.position = mine.position + offset;
        mine.collision_circle.origin = mine.position + mine.collision_circle.initial_origin;
    }

    for(auto enemy = enemies.begin(); enemy != enemies.end();)
    {
        enemy = enemies.erase(enemy);
    }

    last_tile_position = tile_position;

}

