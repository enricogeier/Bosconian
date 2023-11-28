#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <list>
#include "Tile.h"
#include "Enemy.h"
#include "Level.h"
#include "QuadTree.h"




class Level
{
private:

    Tile tiles[9];
    int current_tile_index = 0;

public:

    const int LEVEL_SIZE_X = 4500;
    const int LEVEL_SIZE_Y = 7800;

    const int TILE_SIZE_X = 1500; // default: 2000
    const int TILE_SIZE_Y = 2600; // default: 2667
    const int AMOUNT_OF_TILES_X = 3;
    const int AMOUNT_OF_TILES_Y = 3;

    Vector2 current_tile_position = Vector2();

    explicit Level();

    void initialize_tile_index(Vector2& player_position);

    void set_current_tile(Vector2& player_position);

    void check_tile_positions();

    void set_enemy(std::vector<Rectangle>& sprites, std::vector<Rectangle>& explosion_sprites, CollisionCircle& collision);

    void move_enemies(float& delta, QuadTree& quad_tree);

    void check_enemy_collisions(QuadTree& quad_tree);

    std::vector<Enemy> get_all_game_objects() const;


};



#endif
