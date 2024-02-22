#include "Level.h"

Level::Level()
{

    player = Player(collision_manager.get_player_collision(), collision_manager.scale);
    bullet_handler.previous_player_speed = player.current_velocity;

    load_level();
    fps_timer.start();

}

void Level::initialize_tiles()
{
    for(int j = 0, tile_index = 0; j < Level::AMOUNT_OF_TILES_Y; j++)
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X; i++)
        {
            tiles[tile_index++] = Tile(Vector2(i * Level::TILE_SIZE_X, j * Level::TILE_SIZE_Y));
        }

    }

}

void Level::update(Vector2 player_direction, bool shoot, bool accelerate)
{


    switch(state)
    {

        case WAIT:
        {
            if(timer == std::chrono::microseconds(0))
            {
                auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                timer = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
            }
            else
            {
                auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
                std::chrono::microseconds time_delta = std::chrono::duration_cast<std::chrono::microseconds>(time - timer);

                if(time_delta > std::chrono::microseconds(3000000))
                {
                    timer = std::chrono::microseconds(0);
                    state = LevelState::RUNNING;
                }

            }

            break;
        }
        case RUNNING:
        {
            delta = fps_timer.get_delta();

            if(score.space_stations == 0)
            {

                for(auto& tile : tiles)
                {
                    tile.space_stations.clear();
                    tile.enemies.clear();
                }

                //TODO: check enemy bullets

                bullet_handler.clear_bullets();
                score.space_stations = 0;
                state = LevelState::FINISHED_LEVEL;
                break;


            }

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
                    --player.lives;

                    if(player.lives < 0)
                    {
                        state = LevelState::GAME_OVER;
                    }
                    else
                    {
                        state = LevelState::LOST_LIVE;

                    }

                    break;
                }
                case State::DESTROY:
                {
                    break;
                }
            }

            // move bullets
            bullet_handler.move_bullets(player, quad_tree, delta);

            // move enemies
            move_enemies();

            // check player collision
            if(player.state == State::NORMAL) [[likely]]
            {
                quad_tree.check_collision(player, score);
            }

            // check bullet collisions
            bullet_handler.check_collisions(quad_tree, score);

            // check object collisions
            check_enemy_collisions();
            break;
        }
        case LOST_LIVE:
        {
            // start timer (5 seconds)

            if(lost_life_timer == std::chrono::microseconds(0))
            {
                auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                lost_life_timer = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
            }
            else
            {
                auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
                std::chrono::microseconds time_delta = std::chrono::duration_cast<std::chrono::microseconds>(time - lost_life_timer);

                if(time_delta > std::chrono::microseconds(5000000))
                {
                    lost_life_timer = std::chrono::microseconds(0);
                    for(auto& tile : tiles)
                    {
                        tile.enemies.clear();
                    }
                    state = LevelState::RESTART;
                }

            }


            delta = fps_timer.get_delta();

            quad_tree = QuadTree(
                    {
                            (int)current_tile_position.x - (int(AMOUNT_OF_TILES_X / 2) * TILE_SIZE_X ),
                            (int)current_tile_position.y - (int(AMOUNT_OF_TILES_Y / 2) * TILE_SIZE_Y ),
                            LEVEL_SIZE_X,
                            LEVEL_SIZE_Y
                    });

            // move bullets
            bullet_handler.move_bullets(player, quad_tree, delta);

            // move enemies
            move_enemies();

            // check bullet collisions
            bullet_handler.check_collisions(quad_tree, score);

            // check object collisions
            check_enemy_collisions();


            break;
        }
        case GAME_OVER:
        {
            // testing



            delta = fps_timer.get_delta();

            quad_tree = QuadTree(
                    {
                            (int)current_tile_position.x - (int(AMOUNT_OF_TILES_X / 2) * TILE_SIZE_X ),
                            (int)current_tile_position.y - (int(AMOUNT_OF_TILES_Y / 2) * TILE_SIZE_Y ),
                            LEVEL_SIZE_X,
                            LEVEL_SIZE_Y
                    });

            // move bullets
            bullet_handler.move_bullets(player, quad_tree, delta);

            // move enemies
            move_enemies();

            // check bullet collisions
            bullet_handler.check_collisions(quad_tree, score);

            // check object collisions
            check_enemy_collisions();

            break;
        }
        case RESTART:
        {
            player.position = start_position;
            player.direction = Vector2(0.0f, -1.0f);
            player.current_velocity = Player::MIN_VELOCITY;
            player.do_acceleration = false;
            set_current_tile();
            player.state = State::NORMAL;
            state = LevelState::WAIT;
            break;
        }
        case FINISHED_LEVEL:
        {
            if(timer == std::chrono::microseconds(0))
            {
                auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                timer = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
            }
            else
            {
                auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                auto time = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
                std::chrono::microseconds time_delta = std::chrono::duration_cast<std::chrono::microseconds>(time - timer);

                if(time_delta > std::chrono::microseconds(5000000))
                {
                    timer = std::chrono::microseconds(0);

                    for(auto& tile : tiles)
                    {
                        tile.objects.clear();
                        tile.mines.clear();
                    }

                    // load next level

                    ++current_round;
                    load_level();

                    state = LevelState::RESTART;

                }

            }

            break;
        }


    }





    fps_timer.clamp_and_print_fps(frame_counter);
    frame_counter++;


}

void Level::load_level()
{
    if(current_round > AMOUNT_OF_ROUNDS)
    {
        current_round = 1;
    }

    initialize_tiles();

    std::vector<SpaceStation> space_stations;
    std::vector<Mine> mines;
    std::vector<GameObject> asteroids;


    std::string filename = LEVEL_FOLDER_LOCATION + std::to_string(current_round) + ".txt";
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
            case 'm':
            {
                Vector2 position;
                while(iss >> position.x >> position.y)
                {
                    mines.push_back(
                            Mine(position, collision_manager.get_mine_collision(), collision_manager.scale)
                            );

                }
                break;
            }
            case 'a':
            {
                Vector2 position;
                while(iss >> position.x >> position.y)
                {
                    asteroids.push_back(GameObject(position,
                                                   collision_manager.get_asteroid_collision(),
                                                   Type::ASTEROID, collision_manager.scale));
                }
                break;
            }
            case 's':
            {
                Vector2 position;
                while(iss >> position.x >> position.y)
                {
                    player.position = position;
                    start_position = position;
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
            if(Vector2::distance(player.position, station.position) < PLAYER_OBJECT_DISTANCE)
            {
                continue;
            }

            if(
                    (int)station.position.x <= (int)tile.tile_position.x + TILE_SIZE_X &&
                    (int)station.position.x >= (int)tile.tile_position.x &&
                    (int)station.position.y <= (int)tile.tile_position.y + TILE_SIZE_Y &&
                    (int)station.position.y >= (int)tile.tile_position.y)
            {
                tile.space_stations.push_back(station);
                score.space_stations++;

                break;
            }
        }

    }

    for(auto& mine : mines)
    {
        for(auto& tile : tiles)
        {

            if(Vector2::distance(player.position, mine.position) < PLAYER_OBJECT_DISTANCE)
            {
                continue;
            }

            if(
                    (int)mine.position.x <= (int)tile.tile_position.x + TILE_SIZE_X &&
                    (int)mine.position.x >= (int)tile.tile_position.x &&
                    (int)mine.position.y <= (int)tile.tile_position.y + TILE_SIZE_Y &&
                    (int)mine.position.y >= (int)tile.tile_position.y
                    )

            {
                tile.insert_object(mine);
                break;
            }
        }
    }

    for(auto& asteroid : asteroids)
    {
        for(auto& tile : tiles)
        {
            if(Vector2::distance(player.position, asteroid.position) < PLAYER_OBJECT_DISTANCE)
            {
                continue;
            }

            if(
                    (int)asteroid.position.x <= (int)tile.tile_position.x + TILE_SIZE_X &&
                    (int)asteroid.position.x >= (int)tile.tile_position.x &&
                    (int)asteroid.position.y <= (int)tile.tile_position.y + TILE_SIZE_Y &&
                    (int)asteroid.position.y >= (int)tile.tile_position.y

                    )
            {
                tile.insert_object(asteroid);
                break;
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

        start_tile = current_tile_index;

        std::cerr << "Invalid position for player. Position has been set to: ( " << player.position.x << ", " << player.position.y << " )." << std::endl;
        check_tile_positions();
    }
    else
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
        {
            if(tiles[i].is_object_within_tile(player.position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y)))
            {
                current_tile_index = i;
                current_tile_position = tiles[current_tile_index].tile_position;

                start_tile = current_tile_index;

                check_tile_positions();



                break;
            }
        }
    }

}


void Level::set_current_tile()
{

    if(!(tiles[current_tile_index].is_object_within_tile(player.position,
                                                         Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y))))
    {
        for(int i = 0; i < Level::AMOUNT_OF_TILES_X * Level::AMOUNT_OF_TILES_Y; i++)
        {
            if(i == current_tile_index)
            {
                continue;
            }
            else if(tiles[i].is_object_within_tile(player.position, Vector2(Level::TILE_SIZE_X, Level::TILE_SIZE_Y)))
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

            if(i == start_tile)
            {
                start_position.x += Level::AMOUNT_OF_TILES_X * Level::TILE_SIZE_X;
            }
        }
        else if((int)tiles[i].tile_position.x > e)
        {
            has_changed = true;
            tiles[i].tile_position.x -= Level::AMOUNT_OF_TILES_X * Level::TILE_SIZE_X;

            if(i == start_tile)
            {
                start_position.x -= Level::AMOUNT_OF_TILES_X * Level::TILE_SIZE_X;
            }
        }

        if((int)tiles[i].tile_position.y < n)
        {
            has_changed = true;
            tiles[i].tile_position.y += Level::AMOUNT_OF_TILES_Y * Level::TILE_SIZE_Y;

            if(i == start_tile)
            {
                start_position.y += Level::AMOUNT_OF_TILES_Y * Level::TILE_SIZE_Y;
            }

        }
        else if((int)tiles[i].tile_position.y > s)
        {
            has_changed = true;
            tiles[i].tile_position.y -= Level::AMOUNT_OF_TILES_Y * Level::TILE_SIZE_Y;

            if(i == start_tile)
            {
                start_position.y -= Level::AMOUNT_OF_TILES_Y * Level::TILE_SIZE_Y;
            }
        }

        if(has_changed)
        {

            tiles[i].update_tile_position();
        }


    }
}



void Level::move_enemies()
{
    if(enemy_timer == std::chrono::microseconds(0))
    {
        auto current_frame_time_point = std::chrono::high_resolution_clock::now();
        enemy_timer = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
    }
    else
    {
        auto current_frame_time_point = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
        std::chrono::microseconds time_delta = std::chrono::duration_cast<std::chrono::microseconds>(time - enemy_timer);

        if(time_delta > std::chrono::microseconds(1000000))
        {
            enemy_timer = std::chrono::microseconds(0);

            // create enemy

            std::random_device rd;
            std::mt19937 mt(rd());

            std::uniform_int_distribution<int> random(0, 8);

            int tile_to_set = random(mt);

            std::uniform_int_distribution<int> randomX(
                    tiles[tile_to_set].tile_position.x,
                    tiles[tile_to_set].tile_position.x + TILE_SIZE_X);
            std::uniform_int_distribution<int> randomY(
                    tiles[tile_to_set].tile_position.y,
                    tiles[tile_to_set].tile_position.y + TILE_SIZE_Y
                    );

            Vector2 enemy_position = Vector2(randomX(mt), randomY(mt));

            if(Vector2::distance(player.position, enemy_position) > 2000)
            {
                int enemy_type = random(mt) % 2;

                if(enemy_type == 0)
                {
                    tiles[tile_to_set].enemies.push_back(Enemy(enemy_position, collision_manager.get_p_type_collision(),
                                                               P_TYPE, collision_manager.scale));
                }
                else
                {
                    tiles[tile_to_set].enemies.push_back(Enemy(enemy_position, collision_manager.get_i_type_collision(),
                                                               I_TYPE, collision_manager.scale));
                }


            }

        }

    }


    for(auto& tile : tiles)
    {
        for(auto enemy = tile.enemies.begin(); enemy != tile.enemies.end();)
        {

            if(enemy->state == State::NORMAL)
            {

                    if(player.state == State::NORMAL)
                    {
                        enemy->move(player.position, delta);
                    }
                    else
                    {
                        Vector2 new_position = player.position.multiply(999.0f);
                        enemy->move(new_position, delta);
                    }

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

                if(tile.tile_position == tiles[current_tile_index].tile_position && player.state == State::NORMAL)
                {
                    if(cannon_timer == std::chrono::microseconds(0))
                    {
                        auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                        cannon_timer = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
                    }
                    else
                    {
                        auto current_frame_time_point = std::chrono::high_resolution_clock::now();
                        auto time = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());
                        std::chrono::microseconds time_delta = std::chrono::duration_cast<std::chrono::microseconds>(time - cannon_timer);

                        if(time_delta > std::chrono::microseconds(2000000))
                        {
                            cannon_timer = std::chrono::microseconds(0);

                            SpaceStation nextStation = tile.space_stations.front();
                            float distance = 9999.0f;

                            for(auto& station : tile.space_stations)
                            {
                                float current_distance = Vector2::distance(player.position, station.position);

                                if( current_distance < distance)
                                {
                                    nextStation = station;
                                    distance = current_distance;
                                }
                            }

                            Cannon nextCannon = nextStation.cannons[0];
                            distance = 9999.0f;

                            for(auto& cannon : nextStation.cannons)
                            {
                                if(cannon.state == State::NORMAL)
                                {
                                    float current_distance = Vector2::distance(player.position, cannon.position);

                                    if(current_distance < distance)
                                    {
                                        nextCannon = cannon;
                                        distance = current_distance;
                                    }
                                }

                            }

                            if(distance <= PLAYER_CANNON_DISTANCE)
                            {
                                // shoot

                                Vector2 shoot_position = nextCannon.position + Vector2(32.0f, 32.0f);
                                Vector2 relative_player_position = player.position + Vector2(32.0f, 32.0f);
                                Vector2 direction = relative_player_position - shoot_position;
                                direction = direction.clamp();

                                bullet_handler.insert_enemy_bullet(shoot_position, direction, collision_manager);

                            }


                        }
                    }
                }



                if(player_collision || defect_cannons == space_station->get_amount_of_cannons())
                {
                    space_station->state = State::EXPLODE;
                    score.increase_score(SPACE_STATION);
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
            quad_tree.check_collision(enemy, score);
        }
        for(auto& mine : tile.mines)
        {
            quad_tree.check_collision(mine, score);
        }
        for(auto& object : tile.objects)
        {
            quad_tree.check_collision(object, score);
        }
        for(auto& station : tile.space_stations)
        {
            quad_tree.check_collision(station, score);

            for(auto& cannon : station.cannons)
            {
                quad_tree.check_collision(cannon, score);
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

std::list<Bullet> Level::get_player_bullets() const
{
    return bullet_handler.get_player_bullets();
}

std::list<Bullet> Level::get_enemy_bullets() const
{
    return bullet_handler.get_enemy_bullets();
}

const long& Level::get_current_frame() const
{
    return frame_counter;
}