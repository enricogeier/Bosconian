#include "Level.h"
#include "SpriteSheet.h"

Level::Level()
{
    for(int j = 0, tile_index = 0; j < AMOUNT_OF_TILES_Y; j++)
    {
        for(int i = 0; i < AMOUNT_OF_TILES_X; i++)
        {
            tiles[tile_index++] = Tile(Vector2(i * TILE_SIZE_X, j * TILE_SIZE_Y));
        }

    }
}

void Level::initialize_tile_index(Vector2 &player_position)
{
    if(player_position.x < 0.0f || player_position.y < 0.0f || player_position.x > LEVEL_SIZE_X || player_position.y > LEVEL_SIZE_Y)
    {
        player_position = Vector2(AMOUNT_OF_TILES_X / 2, AMOUNT_OF_TILES_Y / 2);
        current_tile_index = (AMOUNT_OF_TILES_X * AMOUNT_OF_TILES_Y) / 2;
        std::cerr << "Invalid position for player. Position has been set to: ( " << player_position.x << ", " << player_position.y << " )." << std::endl;

    }
    else
    {
        for(int i = 0; i < AMOUNT_OF_TILES_X * AMOUNT_OF_TILES_Y; i++)
        {
            if(tiles[i].is_player_within_tile(player_position, Vector2(TILE_SIZE_X, TILE_SIZE_Y)))
            {
                if(tiles[i].tile_position == Vector2(LEVEL_SIZE_X - (2 * TILE_SIZE_X), LEVEL_SIZE_Y - (2 * TILE_SIZE_Y)))
                {
                    current_tile_index = i;
                    break;
                }

                current_tile_index = i;
                check_tile_positions();



                break;
            }
        }
    }

    std::cout << current_tile_index << std::endl;
}


void Level::set_current_tile(Vector2 &player_position)
{

    if(player_position.y < 0.0f)
    {
        int a = 0;
    }



    if(!(tiles[current_tile_index].is_player_within_tile(player_position, Vector2(TILE_SIZE_X, TILE_SIZE_Y))))
    {
        for(int i = 0; i < AMOUNT_OF_TILES_X * AMOUNT_OF_TILES_Y; i++)
        {
            if(i == current_tile_index)
            {
                continue;
            }
            else if(tiles[i].is_player_within_tile(player_position, Vector2(TILE_SIZE_X, TILE_SIZE_Y)))
            {
                current_tile_index = i;
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
    int n = (int)tile_position.y - TILE_SIZE_Y;
    int s = (int)tile_position.y + TILE_SIZE_Y;
    int w = (int)tile_position.x - TILE_SIZE_X;
    int e = (int)tile_position.x + TILE_SIZE_X;


    for(int i = 0; i < AMOUNT_OF_TILES_X * AMOUNT_OF_TILES_Y; i++)
    {
        if(i == current_tile_index)
        {
            continue;
        }

        bool has_changed = false;

        if((int)tiles[i].tile_position.x < w)
        {
            has_changed = true;
            tiles[i].tile_position.x += AMOUNT_OF_TILES_X * TILE_SIZE_X;
        }
        else if((int)tiles[i].tile_position.x > e)
        {
            has_changed = true;
            tiles[i].tile_position.x -= AMOUNT_OF_TILES_X * TILE_SIZE_X;
        }

        if((int)tiles[i].tile_position.y < n)
        {
            has_changed = true;
            tiles[i].tile_position.y += AMOUNT_OF_TILES_Y * TILE_SIZE_Y;
        }
        else if((int)tiles[i].tile_position.y > s)
        {
            has_changed = true;
            tiles[i].tile_position.y -= AMOUNT_OF_TILES_Y * TILE_SIZE_Y;
        }

        if(has_changed)
        {

            tiles[i].update_tile_position();
        }


    }
}

void Level::spawn_enemy(Vector2& player_position)
{
    // testing

    tiles[0].objects_in_tile.push_back(GameObject(Vector2(250, 250), SpriteSheet::get_e_type(false), SpriteSheet::get_explosion_1()));
}

std::vector<GameObject> Level::get_all_game_objects() const
{
    std::vector<GameObject> game_objects;

    for(auto& tile: tiles)
    {
        for(auto& object : tile.objects_in_tile)
        {
            game_objects.push_back(object);
        }
    }

    return game_objects;
}