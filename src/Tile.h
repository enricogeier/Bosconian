#ifndef TILE_H
#define TILE_H

#include "Vector2.h"
#include "Enemy.h"
#include "Mine.h"
#include "SpaceStation.h"


class Tile
{
private:
    float MIN_DISTANCE = 200.0f;
public:

    Vector2 tile_position;
    Vector2 last_tile_position;

    std::list<Mine> mines;
    std::list<GameObject> objects;
    std::list<Enemy> enemies;
    std::list<SpaceStation> space_stations;

    explicit Tile(Vector2 position = Vector2(0.0f, 0.0f));

    bool is_object_within_tile(Vector2& player_position, Vector2 tile_size) const;

    void update_tile_position();

    void insert_object(Mine& mine);

    void insert_object(GameObject& object);

    void clear();

};



#endif
