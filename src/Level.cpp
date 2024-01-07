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
    bullet_handler.previous_player_speed = player.current_velocity;

    load_level(1);
    fps_timer.start();

}

void Level::update(Vector2 player_direction, bool shoot, bool accelerate)
{

    delta = fps_timer.get_delta();

    quad_tree = QuadTree(
            {
                    (int)current_tile_position.x - (int(AMOUNT_OF_TILES_X / 2) * TILE_SIZE_X ),
                    (int)current_tile_position.y - (int(AMOUNT_OF_TILES_Y / 2) * TILE_SIZE_Y ),
                    LEVEL_SIZE_X,
                    LEVEL_SIZE_Y
            });



    switch (player.state)
    {
        case State::NORMAL:
        {
            player.move(player_direction, delta, accelerate);

            set_current_tile();
            quad_tree.insert(player);

            if(shoot)
            {
                bullet_handler.insert_player_bullets(player, collision_manager);
            }

            break;
        }
        case State::EXPLODE:
        {
            player.state = State::DESTROY;
            break;
        }
        case State::DESTROY:
        {
            break;
        }
    }

    // move bullets
    bullet_handler.move_player_bullet(player, quad_tree, delta);

    // move enemies
    move_enemies();

    // check player collision
    if(player.state == State::NORMAL)
    {
        quad_tree.check_collision(player);
    }

    // check bullet collisions
    bullet_handler.check_collisions(quad_tree);

    // check object collisions
    check_enemy_collisions();

    fps_timer.clamp_and_print_fps(frame_counter);
    frame_counter++;


}

void Level::load_level(int level)
{
    std::vector<SpaceStation> space_stations;


    std::string filename = LEVEL_FOLDER_LOCATION + std::to_string(level) + ".txt";
    std::ifstream file(filename);

    std::string line;

    while(getline(file, line))
    {
        char type = line[0];

        if(type == '*')
        {
            break;
        }

        line[0] = ' ';
        std::istringstream iss(line);

        switch (type)
        {
            case 'h':
            {
                Vector2 position;
                while(iss >> position.x >> position.y)
                {
                    space_stations.push_back(SpaceStation(position,
                                                          collision_manager.get_space_station_collisions(),
                                                          collision_manager.scale,
                                                          true
                    ));
                }
                break;
            }
            case 'v':
            {
                Vector2 position;
                while(iss >> position.x >> position.y)
                {
                    space_stations.push_back(SpaceStation(position,
                                                          collision_manager.get_space_station_collisions(),
                                                          collision_manager.scale
                    ));
                }
                break;

            }
            case 's':
            {
                Vector2 position;
                while(iss >> position.x >> position.y)
                {
                    player.position = position;
                }
                break;
            }
            default:
            {
                break;
            }
        }


    }

    file.close();


    for(auto& station : space_stations)
    {
        for(auto& tile : tiles)
        {
            if(
                    (int)station.position.x <= (int)tile.tile_position.x + TILE_SIZE_X &&
                    (int)station.position.x >= (int)tile.tile_position.x &&
                    (int)station.position.y <= (int)tile.tile_position.y + TILE_SIZE_Y &&
                    (int)station.position.y >= (int)tile.tile_position.y)
            {
                tile.space_stations.push_back(station);

                break;
            }
        }

    }


    for(auto& tile : tiles)
    {
        for(int i = 0; i < OBJECTS_IN_TILE; i++)
        {

            int x = generate_random_int((int)tile.tile_position.x, (int)tile.tile_position.x + TILE_SIZE_X);
            int y = generate_random_int((int)tile.tile_position.y, (int)tile.tile_position.y + TILE_SIZE_Y);

            Vector2 position = Vector2((float)x, (float)y);

            if(Vector2::distance(player.position, position) < PLAYER_OBJECT_DISTANCE)
            {
                continue;
            }

            int type_of_object = generate_random_int(0, 1);

            if(type_of_object == 0)
            {
                Mine mine = Mine(position,
                                 collision_manager.get_mine_collision(), collision_manager.scale);
                tile.insert_object(mine);
            }
            else
            {
                GameObject game_object = GameObject(position,
                                                    collision_manager.get_asteroid_collision(),
                                                    Type::ASTEROID, collision_manager.scale);

                tile.insert_object(game_object);
            }
        }

    }

    initialize_tile_index();


}


void Level::initialize_tile_index()
{
    if(player.position.x < 0.0f || player.position.y < 0.0f || player.position.x > Level::LEVEL_SIZE_X || player.position.y > Level::LEVEL_SIZE_Y)
    {
        player.position = Vector2(Level::AMOUNT_OF_TILES_X / 2, Level::AMOUNT_OF_TILES_Y / 2);
        current_tile_index = (Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y) / 2;
        current_tile_position = tiles[current_tile_index].tile_position;

        std::cerr << "Invalid position for player. Position has been set to: ( " << player.position.x << ", " << player.position.y << " )." << std::endl;
        check_tile_positions();
    }
    else
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
        {
            if(tiles[i].is_player_within_tile(player.position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y)))
            {
                current_tile_index = i;
                current_tile_position = tiles[current_tile_index].tile_position;
                check_tile_positions();



                break;
            }
        }
    }

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
    // TODO: implement this!


}

void Level::move_enemies()
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


        for(auto space_station = tile.space_stations.begin();
            space_station != tile.space_stations.end();)
        {
            if(space_station->state == State::NORMAL)
            {
                space_station->update_cannons();

                int defect_cannons = 0;
                bool player_collision = false;

                for(Cannon& cannon : space_station->cannons)
                {
                    cannon.check_state();
                    quad_tree.insert(cannon);

                    if(cannon.state != State::NORMAL)
                    {
                        if(cannon.state == State::PLAYER_COLLISION)
                        {
                            player_collision = true;
                            break;
                        }
                        else
                        {
                            ++defect_cannons;
                        }

                    }
                }

                if(player_collision || defect_cannons == space_station->get_amount_of_cannons())
                {
                    space_station->state = State::EXPLODE;
                }
                else
                {
                    quad_tree.insert(*space_station);
                }

                ++space_station;
            }
            else
            {
                space_station = tile.space_stations.erase(space_station);
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
        for(auto& mine : tile.mines)
        {
            quad_tree.check_collision(mine);
        }
        for(auto& object : tile.objects)
        {
            quad_tree.check_collision(object);
        }
        for(auto& station : tile.space_stations)
        {
            quad_tree.check_collision(station);

            for(auto& cannon : station.cannons)
            {
                quad_tree.check_collision(cannon);
            }
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

std::vector<SpaceStation> Level::get_space_stations() const
{
    std::vector<SpaceStation> space_stations;

    for(auto& tile : tiles)
    {
        for(auto& station : tile.space_stations)
        {
            space_stations.push_back(station);
        }
    }

    return space_stations;
}


Player Level::get_player() const
{
    return player;
}

std::list<Bullet> Level::get_bullets() const
{
    return bullet_handler.get_bullets();
}

float Level::generate_random_float(float a, float b)
{
    std::random_device random;
    std::mt19937 generate(random());

    std::uniform_real_distribution<float> distribution(a, b);

    return distribution(generate);
}

int Level::generate_random_int(int a, int b)
{
    std::random_device random;
    std::mt19937 generate(random());

    std::uniform_int_distribution<int> distribution(a, b);

    return distribution(generate);
}


const long& Level::get_current_frame() const
{
    return frame_counter;
}