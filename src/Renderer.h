#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <iostream>
#include <string>
#include <utility>
#include <SDL_image.h>
#include <chrono>
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Mine.h"


enum AnimationState
{
    PLAY,
    FINISHED
};


class AnimationPlayer
{
private:
    std::chrono::microseconds frame_time = std::chrono::microseconds(30000); // 0.2s
    u_short frame = 0;
    std::chrono::microseconds start_time = std::chrono::microseconds(0);
    std::vector<SDL_Rect> explosion_sprites;



public:

    AnimationState animation_state = AnimationState::PLAY;
    Vector2 position;
    unsigned int id;

    explicit AnimationPlayer(std::vector<SDL_Rect> explosion_sprites, Vector2 position, unsigned int id)
    : explosion_sprites(std::move(explosion_sprites)), position(position), id(id)
    {}

    SDL_Rect* get_animation_sprite();




};





class Renderer
{
private:
    Vector2 scale = Vector2(1.0f, 1.0f);

    const int SCREEN_SIZE_WIDTH = 1920;   // small: 960
    const int SCREEN_SIZE_HEIGHT = 1080; // 540

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Vector2 camera;

    SDL_Texture* sprite_sheet_texture = nullptr;

    const std::string WINDOW_TITLE = "Bosconian";

    std::list<AnimationPlayer> animations;


    std::vector<SDL_Rect> get_player_sprites();

    std::vector<SDL_Rect> get_e_type(bool leader = false);

    std::vector<SDL_Rect> get_i_type(bool leader = false);

    std::vector<SDL_Rect> get_p_type(bool leader = false);

    std::vector<SDL_Rect> get_spy();

    SDL_Rect get_mine() const;

    std::vector<SDL_Rect> get_asteroid(short sprite = 0);

    SDL_Rect get_p1_life();

    SDL_Rect get_p2_life();

    std::vector<SDL_Rect> get_explosion_1();

    std::vector<SDL_Rect> get_p1_shoot();

    std::vector<SDL_Rect> get_p2_shoot();


    // constexpr: value is known at compile-time => for compiler
    const SDL_Rect sprites[256] = {
            {0, 0, 16, 16}, // player normal
            {16, 0, 16, 16}, // player diagonal

            {32, 0, 16, 16}, // E-Type normal
            {48, 0, 16, 16},
            {64, 0, 16, 16},
            {80, 0, 16, 16},
            {96, 0, 16, 16},
            {112, 0, 16, 16},

            {128, 0, 16, 16},   // E-Type leader
            {144, 0, 16, 16},
            {160, 0, 16, 16},
            {176, 0, 16, 16},
            {192, 0, 16, 16},
            {208,0, 16, 16},

            {224, 0, 16, 16}, // I-Type normal
            {240, 0, 16, 16},
            {0, 16, 16, 16},
            {16, 16, 16, 16},
            {32, 16, 16, 16},
            {48, 16, 16, 16},

            {64, 16, 16, 16}, // I-Type leader
            {80, 16, 16, 16},
            {96, 16, 16, 16},
            {112, 16, 16, 16},
            {128, 16, 16, 16},
            {144, 16, 16, 16},

            {160, 16, 16, 16}, // P-Type normal
            {176, 16, 16, 16},
            {192, 16, 16, 16},
            {208, 16, 16, 16},
            {224, 16, 16, 16},
            {240, 16, 16, 16},

            {0, 32, 16, 16}, // P-Type leader
            {16, 32, 16, 16},
            {32, 32, 16, 16},
            {48, 32, 16, 16},
            {64, 32, 16, 16},
            {80,32, 16, 16},

            {96, 32, 16, 16}, // Spy-Ship
            {112,32, 16, 16},
            {128,32, 16, 16},
            {144,32, 16, 16},
            {160,32, 16, 16},
            {176,32, 16, 16},

            {192,32, 16, 16}, // Mine

            {208,32, 16, 16}, // Asteroid
            {224,32, 16, 16},
            {240,32, 16, 16},

            {96, 48, 16, 16}, // life p1

            {112, 48, 16, 16}, // life p2

            {0, 160, 16, 16}, // Explosion 1
            {16, 160, 16, 16},
            {32, 160, 16, 16},

            {0, 192, 16, 16}, // p1 shoot
            {16, 192, 16, 16},
            {32, 192, 16, 16},
            {48, 192, 16, 16},

            {64, 192, 16, 16}, // p2 shoot
            {80, 192, 16, 16},
            {96, 192, 16, 16},
            {112, 192, 16, 16},


    };

    void load_sprite_sheet();


public:

    const int SPRITE_SHEET_WIDTH = 256;
    const int SPRITE_SHEET_HEIGHT = 400;
    const std::string PATH_TO_SPRITE_SHEET = "../textures/bosconian.png";


    Renderer();

    ~Renderer();

    void clear_screen();

    void update_screen();

    void render_background_particle(SDL_Rect rectangle, short r, short g, short b, short a);

    void render_player(Player object);

    void render_e_type(Enemy object);

    void render_p_type(Enemy object);

    void render_i_type(Enemy object);

    void render_spy(Enemy object);

    void render_asteroid(GameObject object);

    void render_mine(Mine object);

    void render_space_station(Enemy object);

    void render_bullet(Vector2 position, Vector2 direction);

    void render_animations();

    //void render_collision_box(GameObject& game_object);

    void update_camera(Vector2 position);

    void clear();

    void render_collision_box(GameObject game_object);

    void set_scale(Vector2 scale_sprites);
};










#endif