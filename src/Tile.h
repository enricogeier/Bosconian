#ifndef TILE_H
#define TILE_H

#include <limits>
#include "Vector2.h"
#include "Enemy.h"
#include "CelestialObject.h"


class Tile
{
public:

    Vector2 tile_position;

    std::list<CelestialObject> objects_in_tile;
    std::list<Enemy> enemies_in_tile;

    explicit Tile(Vector2 position = Vector2(0.0f, 0.0f));

    bool is_player_within_tile(Vector2& player_position, Vector2 tile_size) const;

    void update_tile_position();


};



#endif
