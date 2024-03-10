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

    /**
     * Constructs a new Tile object.
     *
     * @param position Represents the tile position. Default value is (0.0f, 0.0f) if not provided.
     */
    explicit Tile(Vector2 position = Vector2(0.0f, 0.0f));

    /**
     * Checks if an object is within this tile.
     *
     * @param position Position to check whether is within tile or not.
     * @param tile_size Size of this tile.
     * @return true if object is within tile, false otherwise.
     */
    bool is_object_within_tile(Vector2& position, Vector2 tile_size) const;

    /**
     * Updates every objects' position within this tile.
     */
    void update_tile_position();

    /**
     * Inserts a mine in this tile.
     *
     * @param mine Mine reference containing mine information.
     */
    void insert_object(Mine& mine);

    /**
     * Inserts an asteroid in this tile.
     *
     * @param object GameObject reference containing asteroid information.
     */
    void insert_object(GameObject& object);

    /**
     * Clears the tile.
     */
    void clear();

};



#endif
