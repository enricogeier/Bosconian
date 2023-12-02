#ifndef TILE_H
#define TILE_H

#include "Vector2.h"
#include "Enemy.h"
#include "Mine.h"


class Tile
{
public:

    Vector2 tile_position;
    Vector2 last_tile_position;

    std::list<Mine> mines;
    std::list<GameObject> objects;
    std::list<Enemy> enemies;

    explicit Tile(Vector2 position = Vector2(0.0f, 0.0f));

    bool is_player_within_tile(Vector2& player_position, Vector2 tile_size) const;

    void update_tile_position();


};



#endif
