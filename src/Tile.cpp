#include "Tile.h"

Tile::Tile(Vector2 position) : tile_position(position), last_tile_position(position)
{
}


bool Tile::is_object_within_tile(Vector2 &player_position, Vector2 tile_size) const
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

    for(auto& space_station : space_stations)
    {
        space_station.position = space_station.position + offset;
        space_station.collision_circle.origin = space_station.position + space_station.collision_circle.initial_origin;

        space_station.update_cannon_positions(offset);
    }

    last_tile_position = tile_position;

}

void Tile::insert_object(Mine &mine)
{
    for(auto& object: objects)
    {
        if(Vector2::distance(mine.position, object.position) < MIN_DISTANCE)
        {
            return;
        }
    }
    for(auto& mine_in_tile : mines)
    {
        if(Vector2::distance(mine.position, mine_in_tile.position) < MIN_DISTANCE)
        {
            return;
        }
    }
    for(auto& enemy : enemies)
    {
        if(Vector2::distance(mine.position, enemy.position) < MIN_DISTANCE)
        {
            return;
        }
    }
    for(auto& station : space_stations)
    {
        if(Vector2::distance(mine.position, station.position) < MIN_DISTANCE)
        {
            return;
        }
        for(auto& cannon : station.cannons)
        {
            if(Vector2::distance(mine.position, cannon.position) < MIN_DISTANCE)
            {
                return;
            }
        }

    }
    mines.push_back(mine);



}

void Tile::insert_object(GameObject &object)
{
    for(auto& object_in_tile: objects)
    {
        if(Vector2::distance(object.position, object.position) < MIN_DISTANCE)
        {
            return;
        }
    }
    for(auto& mine_in_tile : mines)
    {
        if(Vector2::distance(object.position, mine_in_tile.position) < MIN_DISTANCE)
        {
            return;
        }
    }
    for(auto& enemy : enemies)
    {
        if(Vector2::distance(object.position, enemy.position) < MIN_DISTANCE)
        {
            return;
        }
    }
    for(auto& station : space_stations)
    {
        if(Vector2::distance(object.position, station.position) < MIN_DISTANCE)
        {
            return;
        }
        for(auto& cannon : station.cannons)
        {
            if(Vector2::distance(object.position, cannon.position) < MIN_DISTANCE)
            {
                return;
            }
        }

    }

    objects.push_back(object);

}

void Tile::clear()
{
    mines.clear();
    enemies.clear();
    space_stations.clear();
    objects.clear();
}