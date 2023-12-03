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

    player = Player(collision_manager.get_player_collision(), collision_manager.scale);
    initialize_tile_index();
    bullet_handler.previous_player_speed = player.current_velocity;

    // TODO: testing, delete this
    set_enemy();
}

void Level::initialize_quad_tree()
{
    quad_tree = QuadTree(
            {
                    (int)current_tile_position.x - (int(AMOUNT_OF_TILES_X / 2) * TILE_SIZE_X ),
                    (int)current_tile_position.y - (int(AMOUNT_OF_TILES_Y / 2) * TILE_SIZE_Y ),
                    LEVEL_SIZE_X,
                    LEVEL_SIZE_Y
            });
}

void Level::update_player(Vector2& player_direction, float &delta, bool& shoot, bool& accelerate)
{

    player.move(player_direction, delta, accelerate);

    set_current_tile();
    quad_tree.insert(player);

    if(shoot)
    {
        bullet_handler.insert_player_bullets(player, collision_manager);
    }

}

void Level::handle_player_state()
{
    if(player.state == State::EXPLODE)
    {
        player.state = State::DESTROY;
    }

}

void Level::update(float& delta)
{
    // move bullets
    bullet_handler.move_player_bullet(player, quad_tree, delta);

    // move enemies
    move_enemies(delta);

    // check player collision
    if(player.state == State::NORMAL)
    {
        quad_tree.check_collision(player);
    }

    // check bullet collisions
    bullet_handler.check_collisions(quad_tree);

    // check object collisions
    check_enemy_collisions();
}

void Level::initialize_tile_index()
{
    if(player.position.x < 0.0f || player.position.y < 0.0f || player.position.x > Level::LEVEL_SIZE_X || player.position.y > Level::LEVEL_SIZE_Y)
    {
        player.position = Vector2(Level::AMOUNT_OF_TILES_X / 2, Level::AMOUNT_OF_TILES_Y / 2);
        current_tile_index = (Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y) / 2;
        current_tile_position = tiles[current_tile_index].tile_position;

        std::cerr << "Invalid position for player. Position has been set to: ( " << player.position.x << ", " << player.position.y << " )." << std::endl;
    }
    else
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
        {
            if(tiles[i].is_player_within_tile(player.position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y)))
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


void Level::set_current_tile()
{

    if(!(tiles[current_tile_index].is_player_within_tile(player.position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y))))
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
        {
            if(i == current_tile_index)
            {
                continue;
            }
            else if(tiles[i].is_player_within_tile(player.position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y)))
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

void Level::set_enemy()
{
    // TODO: testing, implement this!

    tiles[0].enemies.push_back(Enemy(
            Vector2(250, 250),
            collision_manager.get_e_type_collision(),
            Vector2(),
            Type::E_TYPE,
            collision_manager.scale
            ));


    tiles[0].mines.push_back(Mine(
            Vector2(250, 612),
               collision_manager.get_mine_collision(),
               Type::MINE,
               collision_manager.scale
               ));



    tiles[0].enemies.push_back(Enemy(
            Vector2(512, 612),
            collision_manager.get_spy_collision(),
            Vector2(0, 0),
            Type::SPY,
            collision_manager.scale
            ));


    tiles[0].objects.push_back(GameObject(
            Vector2(612, 250),
            collision_manager.get_asteroid_collision(),
            Type::ASTEROID,
            collision_manager.scale
            ));


}

void Level::move_enemies(float& delta)
{
    for(auto& tile : tiles)
    {
        for(auto enemy = tile.enemies.begin(); enemy != tile.enemies.end();)
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
                    enemy = tile.enemies.erase(enemy);
            }


        }

        for(auto object = tile.objects.begin(); object != tile.objects.end(); )
        {
            if(object->state == State::NORMAL)
            {
                quad_tree.insert(*object);
                ++object;
            }
            else
            {
                object = tile.objects.erase(object);
            }
        }

        for(auto mine = tile.mines.begin(); mine != tile.mines.end();)
        {
            switch (mine->state)
            {
                case State::NORMAL:
                    quad_tree.insert(*mine);
                    ++mine;
                    break;
                case State::EXPLODE:
                    quad_tree.insert(*mine);
                    mine->state = State::MINE_EXPLODE;
                    mine->explode();
                    ++mine;
                    break;
                case State::MINE_EXPLODE:
                    quad_tree.insert(*mine);
                    mine->state = State::MINE_EXPLODED;
                    ++mine;
                    break;
                case State::MINE_EXPLODED:
                    quad_tree.insert(*mine);
                    if(mine->check_explosion())
                    {
                        mine->state = State::DESTROY;
                    }
                    ++mine;
                    break;
                case State::DESTROY:
                    mine = tile.mines.erase(mine);
                    break;
            }




        }
    }

}

void Level::check_enemy_collisions()
{
    for(auto& tile : tiles)
    {
        for(auto& enemy : tile.enemies)
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
        for(auto& asteroid : tile.objects)
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
        for(auto& enemy: tile.enemies)
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
        for(auto& mine : tile.mines)
        {
            mines.push_back(mine);
        }
    }

    return mines;
}

Player Level::get_player() const
{
    return player;
}

std::list<Bullet> Level::get_bullets()
{
    return bullet_handler.get_bullets();
}