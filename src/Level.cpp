#include "Level.h"


Level::Level()
{
    for(int j = 0, tile_index = 0; j < Level::AMOUNT_OF_TILES_Y; j++)
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X; i++)
        {
            tiles[tile_index++] = Tile(Vector2(i * Level::TILE_SIZE_X, j * Level::TILE_SIZE_Y));
        }

    }
}

void Level::initialize_tile_index(Vector2 &player_position)
{
    if(player_position.x < 0.0f || player_position.y < 0.0f || player_position.x > Level::LEVEL_SIZE_X || player_position.y > Level::LEVEL_SIZE_Y)
    {
        player_position = Vector2(Level::AMOUNT_OF_TILES_X / 2, Level::AMOUNT_OF_TILES_Y / 2);
        current_tile_index = (Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y) / 2;
        current_tile_position = tiles[current_tile_index].tile_position;

        std::cerr << "Invalid position for player. Position has been set to: ( " << player_position.x << ", " << player_position.y << " )." << std::endl;
    }
    else
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
        {
            if(tiles[i].is_player_within_tile(player_position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y)))
            {
                if(tiles[i].tile_position == Vector2(Level::LEVEL_SIZE_X - (2 * Level::TILE_SIZE_X), Level::LEVEL_SIZE_Y - (2 * Level::TILE_SIZE_Y)))
                {
                    current_tile_index = i;
                    current_tile_position = tiles[current_tile_index].tile_position;
                    break;
                }

                current_tile_index = i;
                current_tile_position = tiles[current_tile_index].tile_position;
                check_tile_positions();



                break;
            }
        }
    }

    std::cout << current_tile_index << std::endl;
}


void Level::set_current_tile(Vector2 &player_position)
{

    if(!(tiles[current_tile_index].is_player_within_tile(player_position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y))))
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
        {
            if(i == current_tile_index)
            {
                continue;
            }
            else if(tiles[i].is_player_within_tile(player_position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y)))
            {
                current_tile_index = i;
                current_tile_position = tiles[current_tile_index].tile_position;
                check_tile_positions();

                break;
            }
        }
    }

    std::cout << current_tile_index << std::endl;
}

void Level::check_tile_positions()
{
    Vector2 tile_position = tiles[current_tile_index].tile_position;
    int n = (int)tile_position.y - Level::TILE_SIZE_Y;
    int s = (int)tile_position.y + Level::TILE_SIZE_Y;
    int w = (int)tile_position.x - Level::TILE_SIZE_X;
    int e = (int)tile_position.x + Level::TILE_SIZE_X;


    for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
    {
        if(i == current_tile_index)
        {
            continue;
        }

        bool has_changed = false;

        if((int)tiles[i].tile_position.x < w)
        {
            has_changed = true;
            tiles[i].tile_position.x += Level::AMOUNT_OF_TILES_X * Level::TILE_SIZE_X;
        }
        else if((int)tiles[i].tile_position.x > e)
        {
            has_changed = true;
            tiles[i].tile_position.x -= Level::AMOUNT_OF_TILES_X * Level::TILE_SIZE_X;
        }

        if((int)tiles[i].tile_position.y < n)
        {
            has_changed = true;
            tiles[i].tile_position.y += Level::AMOUNT_OF_TILES_Y * Level::TILE_SIZE_Y;
        }
        else if((int)tiles[i].tile_position.y > s)
        {
            has_changed = true;
            tiles[i].tile_position.y -= Level::AMOUNT_OF_TILES_Y * Level::TILE_SIZE_Y;
        }

        if(has_changed)
        {

            tiles[i].update_tile_position();
        }


    }
}

void Level::set_enemy(CollisionManager& collision_manager)
{
    // TODO: testing, implement this!

    tiles[0].enemies_in_tile.push_back(Enemy(
            Vector2(250, 250),
            collision_manager.get_e_type_collision(),
            Vector2(),
            Type::E_TYPE
            ));


    tiles[0].mines_in_tile.push_back(Mine(
            Vector2(250, 612),
               collision_manager.get_mine_collision(),
               Type::MINE
               ));



    tiles[0].enemies_in_tile.push_back(Enemy(
            Vector2(512, 612),
            collision_manager.get_spy_collision(),
            Vector2(0, 0),
            Type::SPY
            ));


    tiles[0].objects_in_tile.push_back(GameObject(
            Vector2(612, 250),
            collision_manager.get_asteroid_collision(),
            Type::ASTEROID
            ));


}

void Level::move_enemies(float &delta, QuadTree &quad_tree)
{
    for(auto& tile : tiles)
    {
        for(auto enemy = tile.enemies_in_tile.begin(); enemy != tile.enemies_in_tile.end();)
        {

            if(enemy->state == State::NORMAL)
            {

                    Vector2 move_direction(0.0f, 0.0f);
                    enemy->move(move_direction, delta);

                    quad_tree.insert(*enemy);

                    ++enemy;
            }
            else
            {
                    enemy = tile.enemies_in_tile.erase(enemy);
            }


        }

        for(auto object = tile.objects_in_tile.begin(); object != tile.objects_in_tile.end(); )
        {
            if(object->state == State::NORMAL)
            {
                quad_tree.insert(*object);
                ++object;
            }
            else
            {
                object = tile.objects_in_tile.erase(object);
            }
        }

        for(auto mine = tile.mines_in_tile.begin(); mine != tile.mines_in_tile.end();)
        {
            if(mine->state == State::NORMAL)
            {
                quad_tree.insert(*mine);
                ++mine;
            }
            else
            {
                mine = tile.mines_in_tile.erase(mine);
            }
        }
    }

}

void Level::check_enemy_collisions(QuadTree &quad_tree)
{
    for(auto& tile : tiles)
    {
        for(auto& enemy : tile.enemies_in_tile)
        {
            quad_tree.check_collision(enemy);
        }
    }
}


std::vector<GameObject> Level::get_all_game_objects() const
{
    std::vector<GameObject> game_objects;

    for(auto& tile: tiles)
    {
        for(auto& asteroid : tile.objects_in_tile)
        {
            game_objects.push_back(asteroid);
        }

    }

    return game_objects;
}

std::vector<Enemy> Level::get_all_enemies() const
{
    std::vector<Enemy> enemies;

    for(auto& tile : tiles)
    {
        for(auto& enemy: tile.enemies_in_tile)
        {
            enemies.push_back(enemy);
        }
    }

    return enemies;
}

std::vector<Mine> Level::get_all_mines() const
{
    std::vector<Mine> mines;

    for(auto& tile : tiles)
    {
        for(auto& mine : tile.mines_in_tile)
        {
            mines.push_back(mine);
        }
    }

    return mines;
}

