#include "Renderer.h"

#include <utility>

SDL_Rect *AnimationPlayer::get_animation_sprite()
{
    auto current_frame_time_point = std::chrono::high_resolution_clock::now();
    auto current_frame_time = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time_point.time_since_epoch());

    if(animation_state == AnimationState::PLAY && frame != explosion_sprites.size())
    {
        if(start_time == std::chrono::microseconds(0))
        {
            start_time = current_frame_time;
        }


        std::chrono::microseconds time_delta = std::chrono::duration_cast<std::chrono::microseconds>(current_frame_time - start_time);

        if(time_delta > frame_time)
        {
            start_time = current_frame_time;
            return &explosion_sprites[frame++];
        }
        else
        {
            return &explosion_sprites[frame];
        }

    }
    else if(frame == explosion_sprites.size())
    {
        animation_state = AnimationState::FINISHED;
    }
}


Renderer::Renderer()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // create window
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, SDL_WINDOW_SHOWN);



    // create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize renderer color. Set the color used for drawing operations (Rect, Line and Clear).
    // Set the color for drawing or filling rectangles, lines, and points, and for SDL_RenderClear().
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    load_sprite_sheet();

}

Renderer::~Renderer()
{
    clear();
}

void Renderer::load_sprite_sheet()
{
    // Initialize PNG loading
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface* sprite_sheet_surface = IMG_Load(PATH_TO_SPRITE_SHEET.c_str());
    if(sprite_sheet_surface == nullptr)
    {
        std::cerr << "sprite sheet could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* sprite_sheet = SDL_CreateTextureFromSurface(renderer, sprite_sheet_surface);
    if(sprite_sheet == nullptr)
    {
        std::cerr << "Could not create sprite sheet texture! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(sprite_sheet_surface);
    sprite_sheet_surface = nullptr;

    sprite_sheet_texture = sprite_sheet;
}

void Renderer::update_screen()
{
    // Update screen
    SDL_RenderPresent(renderer);
}

void Renderer::render_side_bar(const Player& player, const std::vector<SpaceStation> stations)
{


    /*
    SDL_RenderSetViewport(renderer, &hi_score_viewport);
    SDL_RenderCopy(renderer, );
    SDL_RenderSetViewport(renderer, &condition_viewport);
    SDL_RenderCopy(renderer, );
    */


    SDL_RenderSetViewport(renderer, &field_viewport);
    SDL_SetRenderDrawColor(renderer, 0x6C, 0x46, 0x75, 0xFF);
    SDL_Rect background{0, 0, field_viewport.w, field_viewport.h};
    SDL_RenderFillRect(renderer, &background);

    float p_clamped_pos_x = player.position.x;
    float p_clamped_pos_y = player.position.y;

    if((int)p_clamped_pos_x > level->LEVEL_SIZE_X)
    {
        while((int)p_clamped_pos_x > level->LEVEL_SIZE_X)
        {
            p_clamped_pos_x -= (float)level->LEVEL_SIZE_X;
        }
    }
    else if((int)p_clamped_pos_x < 0)
    {
        while((int)p_clamped_pos_x < 0)
        {
            p_clamped_pos_x += (float)level->LEVEL_SIZE_X;
        }
    }

    if((int)p_clamped_pos_y < 0)
    {
        while((int)p_clamped_pos_y < 0)
        {
            p_clamped_pos_y += (float)level->LEVEL_SIZE_Y;
        }
    }
    else if((int)p_clamped_pos_y > level->LEVEL_SIZE_Y)
    {
        while((int)p_clamped_pos_y > level->LEVEL_SIZE_Y)
        {
            p_clamped_pos_y -= (float)level->LEVEL_SIZE_Y;
        }
    }


    Vector2 player_cursor_pos = Vector2(
            p_clamped_pos_x * coefficient.x,
            p_clamped_pos_y * coefficient.y
            );



    SDL_Rect sprite = get_player_cursor();

    SDL_Rect render_quad = {(int)(player_cursor_pos.x), (int)(player_cursor_pos.y),
                            sprite.w * 4, sprite.h * 4};

    SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);



    for(auto& station : stations)
    {
        float s_clamped_pos_x = station.position.x;
        float s_clamped_pos_y = station.position.y;

        if((int)s_clamped_pos_x > level->LEVEL_SIZE_X)
        {
            while((int)s_clamped_pos_x > level->LEVEL_SIZE_X)
            {
                s_clamped_pos_x -= (float)level->LEVEL_SIZE_X;
            }
        }
        else if((int)s_clamped_pos_x < 0)
        {
            while((int)s_clamped_pos_x < 0)
            {
                s_clamped_pos_x += (float)level->LEVEL_SIZE_X;
            }
        }

        if((int)s_clamped_pos_y < 0)
        {
            while((int)s_clamped_pos_y < 0)
            {
                s_clamped_pos_y += (float)level->LEVEL_SIZE_Y;
            }
        }
        else if((int)s_clamped_pos_y > level->LEVEL_SIZE_Y)
        {
            while((int)s_clamped_pos_y > level->LEVEL_SIZE_Y)
            {
                s_clamped_pos_y -= (float)level->LEVEL_SIZE_Y;
            }
        }




        Vector2 station_cursor_pos = Vector2(
                s_clamped_pos_x * coefficient.x,
                s_clamped_pos_y * coefficient.y
        );

        sprite = get_station_cursor();

        render_quad = {(int)(station_cursor_pos.x), (int)(station_cursor_pos.y),
                                sprite.w * 4, sprite.h * 4};

        SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);










    }




    SDL_RenderSetViewport(renderer, &game_state_viewport);
    sprite = get_p1_life();

    for(int i = 0; i < player.lives; i++)
    {
        // sprite size: 64 * 64
        render_quad = {i * 64, 0, 64, 64};
        SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

    }





}


void Renderer::render_player(const Player& object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(object.state == State::NORMAL)
    {

        bool diagonal_sprite = false;
        float rotation = 0;

        if(object.direction.x == 0.0f)
        {
            if(object.direction.y == 1.0f)
            {
                rotation = 180.0f;
            }
        }
        else if(object.direction.x == 1.0f)
        {

            if(object.direction.y == 0.0f)
            {
                rotation = 90.0f;
            }
            else if(object.direction.y == 1.0f)
            {
                diagonal_sprite = true;
                rotation = 180.0f;
            }
            else if(object.direction.y == -1.0f)
            {
                rotation = 90.0f;
                diagonal_sprite = true;
            }
        }
        else if(object.direction.x == -1.0f)
        {

            if(object.direction.y == 0.0f)
            {
                rotation = -90.0f;
            }
            else if(object.direction.y == 1.0f)
            {
                diagonal_sprite = true;
                rotation = -90.0f;
            }
            else if(object.direction.y == -1.0f)
            {
                diagonal_sprite = true;
            }
        }

        SDL_Rect  sprite;

        if(diagonal_sprite)
        {
            sprite = get_player_sprites()[1];
        }
        else
        {
            sprite = get_player_sprites()[0];
        }

        SDL_Rect render_quad = {(int)(object.position.x - camera.x), (int)(object.position.y - camera.y),
                                sprite.w * (int)object.scale.x, sprite.h * (int)object.scale.y};

        SDL_RenderCopyEx(renderer, sprite_sheet_texture, &sprite, &render_quad, rotation, nullptr, SDL_FLIP_NONE);

    }
    else if(object.state == State::EXPLODE)
    {
        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == object.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject &) object));
        }


    }

}



void Renderer::render_e_type(const Enemy& object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(object.state == State::NORMAL)
    {
        // TODO: Testing, change in each moving enemy render function!

        float rotation = 0.0f;
        SDL_Rect sprite = get_e_type()[0];

        SDL_Rect render_quad = {(int)(object.position.x - camera.x), (int)(object.position.y - camera.y),
                                sprite.w * (int)object.scale.x, sprite.h * (int)object.scale.y};

        SDL_RenderCopyEx(renderer, sprite_sheet_texture, &sprite, &render_quad, rotation, nullptr, SDL_FLIP_NONE);

    }
    else if(object.state == State::EXPLODE)
    {


        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == object.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject &) object));
        }




    }
}

void Renderer::render_p_type(const Enemy& object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(object.state == State::NORMAL)
    {
        // TODO: Testing, change in each moving enemy render function!

        float rotation = 0.0f;
        SDL_Rect sprite = get_p_type()[0];

        SDL_Rect render_quad = {(int)(object.position.x - camera.x), (int)(object.position.y - camera.y),
                                sprite.w * (int)object.scale.x, sprite.h * (int)object.scale.y};

        SDL_RenderCopyEx(renderer, sprite_sheet_texture, &sprite, &render_quad, rotation, nullptr, SDL_FLIP_NONE);

    }
    else if(object.state == State::EXPLODE)
    {
        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == object.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject &) object));
        }



    }
}

void Renderer::render_i_type(const Enemy& object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(object.state == State::NORMAL)
    {
        // TODO: Testing, change in each moving enemy render function!

        float rotation = 0.0f;
        SDL_Rect sprite = get_i_type()[0];

        SDL_Rect render_quad = {(int)(object.position.x - camera.x), (int)(object.position.y - camera.y),
                                sprite.w * (int)object.scale.x, sprite.h * (int)object.scale.y};

        SDL_RenderCopyEx(renderer, sprite_sheet_texture, &sprite, &render_quad, rotation, nullptr, SDL_FLIP_NONE);

    }
    else if(object.state == State::EXPLODE)
    {
        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == object.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject &) object));
        }




    }
}

void Renderer::render_spy(const Enemy& object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(object.state == State::NORMAL)
    {
        // TODO: Testing, change in each moving enemy render function!

        float rotation = 0.0f;
        SDL_Rect sprite = get_spy()[0];

        SDL_Rect render_quad = {(int)(object.position.x - camera.x), (int)(object.position.y - camera.y),
                                sprite.w * (int)object.scale.x, sprite.h * (int)object.scale.y};

        SDL_RenderCopyEx(renderer, sprite_sheet_texture, &sprite, &render_quad, rotation, nullptr, SDL_FLIP_NONE);

    }
    else if(object.state == State::EXPLODE)
    {
        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == object.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject &) object));
        }




    }
}

void Renderer::render_asteroid(const GameObject& object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(object.state == State::NORMAL)
    {

        SDL_Rect sprite = get_asteroid(object.id % 3);

        SDL_Rect render_quad = {(int)(object.position.x - camera.x), (int)(object.position.y - camera.y),
                                sprite.w * (int)object.scale.x, sprite.h * (int)object.scale.y};

        SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

    }
    else if(object.state == State::EXPLODE)
    {
        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == object.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject& )object));
        }




    }
}

void Renderer::render_mine(const Mine& object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(object.state == State::NORMAL)
    {
        SDL_Rect sprite = get_mine();

        SDL_Rect render_quad = {(int)(object.position.x - camera.x), (int)(object.position.y - camera.y),
                                sprite.w * (int)object.scale.x, sprite.h * (int)object.scale.y};

        SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

    }
    else if(object.state == State::MINE_EXPLODE)
    {

        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == object.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            animations.push_back(AnimationPlayer(get_mine_explosion(), (GameObject &) object, object.explosion_duration));
        }


    }
}

void Renderer::render_space_station(const SpaceStation& station)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    if(station.state == State::NORMAL)
    {
        if(station.horizontal)
        {

            SDL_Rect sprite = get_space_station_h_core();

            SDL_Rect render_quad = {(int)(station.position.x - camera.x), (int)(station.position.y - camera.y),
                                    sprite.w * (int)station.scale.x, sprite.h * (int)station.scale.y};

            SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

            for(auto& cannon : station.cannons)
            {
                if(cannon.state == State::NORMAL)
                {

                    switch(cannon.type)
                    {

                        case N:
                            sprite = get_cannon_hnn();
                            break;
                        case NE:
                            sprite = get_cannon_hnne();
                            break;
                        case SE:
                            sprite = get_cannon_hnse();
                            break;
                        case S:
                            sprite = get_cannon_hns();
                            break;
                        case SW:
                            sprite = get_cannon_hnsw();
                            break;
                        case NW:
                            sprite = get_cannon_hnnw();
                            break;
                    }

                    render_quad = {(int)(cannon.position.x - camera.x), (int)(cannon.position.y - camera.y),
                                            sprite.w * (int)cannon.scale.x, sprite.h * (int)cannon.scale.y};

                    SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

                }
                else
                {
                    if(cannon.state == State::EXPLODE)
                    {
                        bool found = false;

                        for(auto& animation : animations)
                        {
                            if(animation.id == cannon.id)
                            {
                                found = true;
                                break;
                            }
                        }

                        if(!found)
                        {
                            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject &) cannon));
                        }
                    }
                    switch (cannon.type)
                    {
                        case N:
                            sprite = get_cannon_hen();
                            break;
                        case NE:
                            sprite = get_cannon_hene();
                            break;
                        case SE:
                            sprite = get_cannon_hese();
                            break;
                        case S:
                            sprite = get_cannon_hes();
                            break;
                        case SW:
                            sprite = get_cannon_hesw();
                            break;
                        case NW:
                            sprite = get_cannon_henw();
                            break;
                    }

                    render_quad = {(int)(cannon.position.x - camera.x), (int)(cannon.position.y - camera.y),
                                   sprite.w * (int)cannon.scale.x, sprite.h * (int)cannon.scale.y};

                    SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);
                }
            }


        }
        else
        {
            SDL_Rect sprite = get_space_station_v_core();

            SDL_Rect render_quad = {(int)(station.position.x - camera.x), (int)(station.position.y - camera.y),
                                    sprite.w * (int)station.scale.x, sprite.h * (int)station.scale.y};

            SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

            for(auto& cannon : station.cannons)
            {
                if(cannon.state == State::NORMAL)
                {

                    switch(cannon.type)
                    {
                        case NE:
                            sprite = get_cannon_vnne();
                            break;
                        case E:
                            sprite = get_cannon_vne();
                            break;
                        case SE:
                            sprite = get_cannon_vnse();
                            break;
                        case SW:
                            sprite = get_cannon_vnsw();
                            break;
                        case W:
                            sprite = get_cannon_vnw();
                            break;
                        case NW:
                            sprite = get_cannon_vnnw();
                            break;
                    }

                    render_quad = {(int)(cannon.position.x - camera.x), (int)(cannon.position.y - camera.y),
                                   sprite.w * (int)cannon.scale.x, sprite.h * (int)cannon.scale.y};

                    SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

                }
                else
                {
                    if(cannon.state == State::EXPLODE)
                    {
                        bool found = false;

                        for(auto& animation : animations)
                        {
                            if(animation.id == cannon.id)
                            {
                                found = true;
                                break;
                            }
                        }

                        if(!found)
                        {
                            animations.push_back(AnimationPlayer(get_explosion_1(), (GameObject &) cannon));
                        }
                    }
                    switch (cannon.type)
                    {
                        case NE:
                            sprite = get_cannon_vene();
                            break;
                        case E:
                            sprite = get_cannon_vee();
                            break;
                        case SE:
                            sprite = get_cannon_vese();
                            break;
                        case SW:
                            sprite = get_cannon_vesw();
                            break;
                        case W:
                            sprite = get_cannon_vew();
                            break;
                        case NW:
                            sprite = get_cannon_venw();
                            break;
                    }

                    render_quad = {(int)(cannon.position.x - camera.x), (int)(cannon.position.y - camera.y),
                                   sprite.w * (int)cannon.scale.x, sprite.h * (int)cannon.scale.y};

                    SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);
                }
            }
        }
    }
    else
    {
        bool found = false;

        for(auto& animation : animations)
        {
            if(animation.id == station.id)
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            std::vector<SDL_Rect> explosion_sprites = get_space_station_explosion();

            Vector2 animation_position_0 = station.position - Vector2(16 * station.scale.x, 20 * station.scale.y);
            Vector2 animation_position_1 = animation_position_0 + Vector2(32 * station.scale.x, 0.0f);
            Vector2 animation_position_2 = animation_position_0 + Vector2(0.0f, 32 * station.scale.y);
            Vector2 animation_position_3 = animation_position_0 + Vector2(32 * station.scale.x, 32 * station.scale.y);


            animations.push_back(AnimationPlayer(explosion_sprites, animation_position_0,
                                                 station.id, station.scale));
            animations.push_back(AnimationPlayer(explosion_sprites, animation_position_1,
                                                 station.id, station.scale));
            animations.push_back(AnimationPlayer(explosion_sprites, animation_position_2,
                                                 station.id, station.scale));
            animations.push_back(AnimationPlayer(explosion_sprites, animation_position_3,
                                                 station.id, station.scale));


        }
    }




}


void Renderer::render_bullet(const Bullet& bullet)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    SDL_Rect sprite;

    if(bullet.direction.x == 0.0f)
    {
        sprite = get_p1_shoot()[0];
    }
    else if(bullet.direction.x == 1.0f)
    {
        if(bullet.direction.y == 1.0f)
        {
            sprite = get_p1_shoot()[1];
        }
        else if(bullet.direction.y == -1.0f)
        {
            sprite = get_p1_shoot()[3];
        }
        else if(bullet.direction.y == 0.0f)
        {
            sprite = get_p1_shoot()[2];
        }
    }
    else if(bullet.direction.x == -1.0f)
    {

        if(bullet.direction.y == 1.0f)
        {
            sprite = get_p1_shoot()[3];
        }
        else if(bullet.direction.y == -1.0f)
        {
            sprite = get_p1_shoot()[1];
        }
        else if(bullet.direction.y == 0.0f)
        {
            sprite = get_p1_shoot()[2];
        }
    }

    SDL_Rect render_quad = {(int)(bullet.position.x - camera.x), (int)(bullet.position.y - camera.y),
                            sprite.w * (int)bullet.scale.x, sprite.h * (int)bullet.scale.y};

    SDL_RenderCopy(renderer, sprite_sheet_texture, &sprite, &render_quad);

}



void Renderer::render_animations()
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    for(auto animation = animations.begin(); animation != animations.end();)
    {
        SDL_Rect* sprite = animation->get_animation_sprite();
        SDL_Rect render_quad = {(int)(animation->position.x - camera.x), (int)(animation->position.y - camera.y),
                                sprite->w * (int)animation->scale.x, sprite->h * (int)animation->scale.y};

        SDL_RenderCopy(renderer, sprite_sheet_texture, sprite, &render_quad);

        if(animation->animation_state == AnimationState::FINISHED)
        {
            animation = animations.erase(animation);
        }
        else
        {
            animation++;
        }
    }
}





void Renderer::render_collision_box(const GameObject& game_object)
{
    SDL_RenderSetViewport(renderer, &game_viewport);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

    for(int y = (int)-game_object.collision_circle.radius; y <= (int)game_object.collision_circle.radius; ++y)
    {
        for(int x = (int)-game_object.collision_circle.radius; x <= (int) game_object.collision_circle.radius; ++x)
        {
            if(x * x + y * y  <= (int)game_object.collision_circle.radius * (int)game_object.collision_circle.radius)
            {
                SDL_RenderDrawPoint(renderer, (int)game_object.collision_circle.origin.x + x - (int)camera.x,
                                    (int)game_object.collision_circle.origin.y + y - (int)camera.y);
            }
        }
    }

    /*
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y -  camera.y,
            game_object.collision_circle.origin.x + game_object.collision_circle.radius - camera.x,
            game_object.collision_circle.origin.y - camera.y
            );
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - camera.y,
            game_object.collision_circle.origin.x - game_object.collision_circle.radius - camera.x,
            game_object.collision_circle.origin.y - camera.y
    );
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - camera.y,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y + game_object.collision_circle.radius  - camera.y
    );
    SDL_RenderDrawLineF(
            renderer,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - camera.y,
            game_object.collision_circle.origin.x - camera.x,
            game_object.collision_circle.origin.y - game_object.collision_circle.radius  - camera.y
    );

    */

}



void Renderer::clear()
{
    // destroy sprite sheet

    if(sprite_sheet_texture != nullptr)
    {
        SDL_DestroyTexture(sprite_sheet_texture);
        sprite_sheet_texture = nullptr;
    }

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

void Renderer::update_camera(const Player* player)
{
    SDL_Rect sprite = get_player_sprites().front();
    Vector2 sprite_size((float)sprite.w, (float)sprite.h);

    camera = Vector2((player->position.x + (sprite_size.x / 2)) - ((float)game_viewport.w / 2),
                     (player->position.y + (sprite_size.y / 2)) - ((float)game_viewport.h / 2));
}

void Renderer::clear_screen()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
}


void Renderer::update()
{
    clear_screen();

    const Player player = level->get_player();
    update_camera(&player);

    render_animations();


    const std::vector<GameObject> asteroids = level->get_all_game_objects();

    for(auto& asteroid : asteroids)
    {
        render_asteroid(asteroid);
    }

    const std::vector<Mine> mines = level->get_all_mines();

    for(auto& mine : mines)
    {
       render_mine(mine);
    }

    const std::vector<Enemy> enemies = level->get_all_enemies();

    for(auto& enemy : enemies)
    {
        switch (enemy.type)
        {
            case E_TYPE:
                render_e_type(enemy);
                break;
            case P_TYPE:
                render_p_type(enemy);
                break;
            case I_TYPE:
                render_i_type(enemy);
                break;
            case SPY:
                render_spy(enemy);
                break;
        }
    }

    const std::vector<SpaceStation> stations = level->get_space_stations();
    for(auto& station : stations)
    {
        render_space_station(station);


    }

    const std::list<Bullet> bullet_list = level->get_bullets();
    for(auto& bullet : bullet_list)
    {
        render_bullet(bullet);
    }

    render_player(player);

    render_side_bar(player, stations);

    update_screen();

}

void Renderer::set_level(const Level *level)
{
    this->level = level;
    coefficient = Vector2(
            (float)field_viewport.w / (float)level->LEVEL_SIZE_X,
            (float)field_viewport.h / (float)level->LEVEL_SIZE_Y);
}



std::vector<SDL_Rect> Renderer::get_player_sprites() const
{
    std::vector<SDL_Rect> sprite_list;

    sprite_list.push_back(sprites[0]);
    sprite_list.push_back(sprites[1]);

    return sprite_list;
}


std::vector<SDL_Rect> Renderer::get_e_type(bool leader) const
{
    std::vector<SDL_Rect> sprite_list;

    if(!leader)
    {
        sprite_list.push_back(sprites[2]);
        sprite_list.push_back(sprites[3]);
        sprite_list.push_back(sprites[4]);
        sprite_list.push_back(sprites[5]);
        sprite_list.push_back(sprites[6]);
        sprite_list.push_back(sprites[7]);
    }
    else
    {
        sprite_list.push_back(sprites[8]);
        sprite_list.push_back(sprites[9]);
        sprite_list.push_back(sprites[10]);
        sprite_list.push_back(sprites[11]);
        sprite_list.push_back(sprites[12]);
        sprite_list.push_back(sprites[13]);

    }
    return sprite_list;
}

std::vector<SDL_Rect> Renderer::get_i_type(bool leader) const
{
    std::vector<SDL_Rect> sprite_list;

    if(!leader)
    {
        sprite_list.push_back(sprites[14]);
        sprite_list.push_back(sprites[15]);
        sprite_list.push_back(sprites[16]);
        sprite_list.push_back(sprites[17]);
        sprite_list.push_back(sprites[18]);
        sprite_list.push_back(sprites[19]);
    }
    else
    {
        sprite_list.push_back(sprites[20]);
        sprite_list.push_back(sprites[21]);
        sprite_list.push_back(sprites[22]);
        sprite_list.push_back(sprites[23]);
        sprite_list.push_back(sprites[24]);
        sprite_list.push_back(sprites[25]);

    }
    return sprite_list;
}

std::vector<SDL_Rect> Renderer::get_p_type(bool leader) const
{
    std::vector<SDL_Rect> sprite_list;

    if(!leader)
    {
        sprite_list.push_back(sprites[26]);
        sprite_list.push_back(sprites[27]);
        sprite_list.push_back(sprites[28]);
        sprite_list.push_back(sprites[29]);
        sprite_list.push_back(sprites[30]);
        sprite_list.push_back(sprites[31]);
    }
    else
    {
        sprite_list.push_back(sprites[32]);
        sprite_list.push_back(sprites[33]);
        sprite_list.push_back(sprites[34]);
        sprite_list.push_back(sprites[35]);
        sprite_list.push_back(sprites[36]);
        sprite_list.push_back(sprites[37]);

    }
    return sprite_list;
}

std::vector<SDL_Rect> Renderer::get_spy() const
{
    std::vector<SDL_Rect> sprite_list;

    sprite_list.push_back(sprites[38]);
    sprite_list.push_back(sprites[39]);
    sprite_list.push_back(sprites[40]);
    sprite_list.push_back(sprites[41]);
    sprite_list.push_back(sprites[42]);
    sprite_list.push_back(sprites[43]);

    return sprite_list;
}

SDL_Rect Renderer::get_mine() const
{
    return sprites[44];
}

SDL_Rect Renderer::get_asteroid(const unsigned int& sprite) const
{

    if(sprite >= 0 && sprite < 3)
    {
        return sprites[45 + sprite];
    }
    else
    {
        std::cerr << "wrong sprite number for get_asteroid()" << std::endl;
    }
}

SDL_Rect Renderer::get_p1_life() const
{
    return sprites[48];
}

SDL_Rect Renderer::get_p2_life() const
{
    return sprites[49];
}

std::vector<SDL_Rect> Renderer::get_explosion_1() const
{
    std::vector<SDL_Rect> sprite_list;

    sprite_list.push_back(sprites[50]);
    sprite_list.push_back(sprites[51]);
    sprite_list.push_back(sprites[52]);

    return sprite_list;
}

std::vector<SDL_Rect> Renderer::get_p1_shoot() const
{
    std::vector<SDL_Rect> sprite_list;

    sprite_list.push_back(sprites[53]);
    sprite_list.push_back(sprites[54]);
    sprite_list.push_back(sprites[55]);
    sprite_list.push_back(sprites[56]);

    return sprite_list;
}

std::vector<SDL_Rect> Renderer::get_p2_shoot() const
{
    std::vector<SDL_Rect> sprite_list;

    sprite_list.push_back(sprites[57]);
    sprite_list.push_back(sprites[58]);
    sprite_list.push_back(sprites[59]);
    sprite_list.push_back(sprites[60]);

    return sprite_list;
}

std::vector<SDL_Rect> Renderer::get_mine_explosion() const
{
    std::vector<SDL_Rect> sprite_list;
    sprite_list.push_back(sprites[61]);
    sprite_list.push_back(sprites[62]);
    sprite_list.push_back(sprites[63]);

    return sprite_list;
}

std::vector<SDL_Rect> Renderer::get_space_station_explosion() const
{
    std::vector<SDL_Rect > sprite_list;
    sprite_list.push_back(sprites[90]);
    sprite_list.push_back(sprites[91]);
    sprite_list.push_back(sprites[92]);

    return sprite_list;
}

SDL_Rect Renderer::get_space_station_h_core() const
{
    return sprites[64];
}

SDL_Rect Renderer::get_space_station_v_core() const
{
    return sprites[65];
}

SDL_Rect Renderer::get_cannon_hnn() const
{
    return sprites[66];
}

SDL_Rect Renderer::get_cannon_hnne() const
{
    return sprites[67];
}

SDL_Rect Renderer::get_cannon_hnse() const
{
    return sprites[68];
}

SDL_Rect Renderer::get_cannon_hns() const
{
    return sprites[69];
}

SDL_Rect Renderer::get_cannon_hnsw() const
{
    return sprites[70];
}

SDL_Rect Renderer::get_cannon_hnnw() const
{
    return sprites[71];
}

SDL_Rect Renderer::get_cannon_hen() const
{
    return sprites[72];
}

SDL_Rect Renderer::get_cannon_hene() const
{
    return sprites[73];
}

SDL_Rect Renderer::get_cannon_hese() const
{
    return sprites[74];
}

SDL_Rect Renderer::get_cannon_hes() const
{
    return sprites[75];
}

SDL_Rect Renderer::get_cannon_hesw() const
{
    return sprites[76];
}

SDL_Rect Renderer::get_cannon_henw() const
{
    return sprites[77];
}

SDL_Rect Renderer::get_cannon_vnw() const
{
    return sprites[78];
}

SDL_Rect Renderer::get_cannon_vnnw() const
{
    return sprites[79];
}

SDL_Rect Renderer::get_cannon_vnne() const
{
    return sprites[80];
}

SDL_Rect Renderer::get_cannon_vne() const
{
    return sprites[81];
}

SDL_Rect Renderer::get_cannon_vnse() const
{
    return sprites[82];
}

SDL_Rect Renderer::get_cannon_vnsw() const
{
    return sprites[83];
}

SDL_Rect Renderer::get_cannon_vew() const
{
    return sprites[84];
}

SDL_Rect Renderer::get_cannon_venw() const
{
    return sprites[85];
}

SDL_Rect Renderer::get_cannon_vene() const
{
    return sprites[86];
}

SDL_Rect Renderer::get_cannon_vee() const
{
    return sprites[87];
}

SDL_Rect Renderer::get_cannon_vese() const
{
    return sprites[88];
}

SDL_Rect Renderer::get_cannon_vesw() const
{
    return sprites[89];
}

SDL_Rect Renderer::get_player_cursor() const
{
    return sprites[93];
}

SDL_Rect Renderer::get_station_cursor() const
{
    return sprites[94];
}