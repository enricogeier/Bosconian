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

void Level::set_enemy(std::vector<Rectangle>& sprites, std::vector<Rectangle>& explosion_sprites, CollisionCircle& collision)
{
    // TODO: testing, implement this!
    tiles[0].objects_in_tile.push_back(Enemy(
            Vector2(250, 250),
            sprites, explosion_sprites, collision
            ));

}

void Level::move_enemies(float &delta, QuadTree &quad_tree)
{
    for(auto& tile : tiles)
    {
        for(auto enemy = tile.objects_in_tile.begin(); enemy != tile.objects_in_tile.end();)
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
                enemy = tile.objects_in_tile.erase(enemy);
            }
        }
    }
}

void Level::check_enemy_collisions(QuadTree &quad_tree)
{
    for(auto& tile : tiles)
    {
        for(auto& enemy : tile.objects_in_tile)
        {
            quad_tree.check_collision(enemy);
        }
    }
}


std::vector<Enemy> Level::get_all_game_objects() const
{
    std::vector<Enemy> enemies;

    for(auto& tile: tiles)
    {
        for(auto& enemy : tile.objects_in_tile)
        {
            enemies.push_back(enemy);
        }
    }

    return enemies;
}

void Level::delete_enemy(Enemy &enemy)
{
    for(auto& tile : tiles)
    {
        for(auto& enemy_in_tile : tile.objects_in_tile)
        {
            if(enemy_in_tile == enemy)
            {
                tile.objects_in_tile.remove(enemy_in_tile);
                return;
            }
        }
    }
}