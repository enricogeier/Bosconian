#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <string>
#include <utility>
#include <SDL_image.h>
#include <chrono>
#include <random>
#include <map>
#include "Level.h"



enum AnimationState
{
    PLAY,
    FINISHED
};


class AnimationPlayer
{
private:
    std::chrono::microseconds duration = std::chrono::microseconds(250000);
    std::chrono::microseconds frame_time;
    u_short frame = 0;
    std::chrono::microseconds start_time = std::chrono::microseconds(0);
    std::vector<SDL_Rect> explosion_sprites;


public:

    AnimationState animation_state = AnimationState::PLAY;
    Vector2 position;
    unsigned int id;

    AnimationPlayer(std::vector<SDL_Rect> explosion_sprites, GameObject& game_object)
    : position(game_object.position), id(game_object.id), scale(game_object.scale), frame_time(std::chrono::microseconds(0))
    {
        this->explosion_sprites = std::move(explosion_sprites);
        frame_time = std::chrono::duration_cast<std::chrono::microseconds>(duration / this->explosion_sprites.size());

    }

    AnimationPlayer(std::vector<SDL_Rect> explosion_sprites, GameObject& game_object, std::chrono::microseconds duration)
            : position(game_object.position), id(game_object.id), scale(game_object.scale),
            frame_time(std::chrono::microseconds(0)), duration(duration)
    {
        this->explosion_sprites = std::move(explosion_sprites);
        frame_time = std::chrono::duration_cast<std::chrono::microseconds>(duration / this->explosion_sprites.size());

    }

    AnimationPlayer(std::vector<SDL_Rect> explosion_sprites, Vector2& position, const unsigned int& id, const Vector2& scale)
    : position(position), id(id), scale(scale), frame_time(std::chrono::microseconds(0))
    {
        this->explosion_sprites = std::move(explosion_sprites);
        frame_time = std::chrono::duration_cast<std::chrono::microseconds>(duration / this->explosion_sprites.size());
    }

    SDL_Rect* get_animation_sprite();


    Vector2 scale = Vector2(1.0f, 1.0f);
};

enum Color
{
    RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN
};

class Renderer
{
private:

    const int SCREEN_SIZE_WIDTH = 1920;   // small: 960
    const int SCREEN_SIZE_HEIGHT = 1080; // 540


    const std::string PATH_TO_SPRITE_SHEET = "../textures/bosconian.png";

    const Level* level = nullptr;
    Vector2 coefficient = Vector2();


    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Vector2 camera;

    SDL_Texture* sprite_sheet_texture = nullptr;

    const std::string WINDOW_TITLE = "Bosconian";

    const SDL_Rect game_viewport{0, 0, 1488, 1080};
    const SDL_Rect hi_score_viewport{1488, 0, 432, 234};
    const SDL_Rect condition_viewport{1488, 234, 432, 144};
    const SDL_Rect field_viewport{1488, 378, 432, 540};
    const SDL_Rect game_state_viewport{1488, 918, 432, 162};

    std::map<Color, SDL_Color> color_values = {
            {Color::RED, SDL_Color{255, 0, 0, 255}},
            {Color::GREEN, SDL_Color{0, 255, 0, 255}},
            {Color::BLUE, SDL_Color{0, 0, 255, 255}},
            {Color::YELLOW, SDL_Color{255, 255, 0, 255}},
            {Color::MAGENTA, SDL_Color{255, 0, 255, 255}},
            {Color::CYAN, SDL_Color{0, 255, 255, 255}},
    };

    std::map<Color, SDL_Point> points;

    std::chrono::microseconds point_timer = std::chrono::microseconds(0);

    const uint16_t NUM_PARTICLES = 1250;  // default: 1250
    const u_short GRID_SIZE = 4; // default: 4


    int colors[24] = {
            255, 0, 0, 255, // red
            0, 255, 0, 255,  // green
            0, 0, 255, 255,  // blue
            255, 255, 0, 255, // yellow
            255, 0, 255, 255, // magenta
            0, 255, 255, 255 // cyan
    };



    std::list<AnimationPlayer> animations;

    // constexpr: value is known at compile-time => for compiler
    const SDL_Rect sprites[256] = {
            {0,   0,   16, 16}, // player normal
            {16,  0,   16, 16}, // player diagonal

            {32,  0,   16, 16}, // E-Type normal
            {48,  0,   16, 16},
            {64,  0,   16, 16},
            {80,  0,   16, 16},
            {96,  0,   16, 16},
            {112, 0,   16, 16},

            {128, 0,   16, 16},   // E-Type leader
            {144, 0,   16, 16},
            {160, 0,   16, 16},
            {176, 0,   16, 16},
            {192, 0,   16, 16},
            {208, 0,   16, 16},

            {224, 0,   16, 16}, // I-Type normal
            {240, 0,   16, 16},
            {0,   16,  16, 16},
            {16,  16,  16, 16},
            {32,  16,  16, 16},
            {48,  16,  16, 16},

            {64,  16,  16, 16}, // I-Type leader
            {80,  16,  16, 16},
            {96,  16,  16, 16},
            {112, 16,  16, 16},
            {128, 16,  16, 16},
            {144, 16,  16, 16},

            {160, 16,  16, 16}, // P-Type normal
            {176, 16,  16, 16},
            {192, 16,  16, 16},
            {208, 16,  16, 16},
            {224, 16,  16, 16},
            {240, 16,  16, 16},

            {0,   32,  16, 16}, // P-Type leader
            {16,  32,  16, 16},
            {32,  32,  16, 16},
            {48,  32,  16, 16},
            {64,  32,  16, 16},
            {80,  32,  16, 16},

            {96,  32,  16, 16}, // Spy-Ship
            {112, 32,  16, 16},
            {128, 32,  16, 16},
            {144, 32,  16, 16},
            {160, 32,  16, 16},
            {176, 32,  16, 16},

            {192, 32,  16, 16}, // Mine

            {208, 32,  16, 16}, // Asteroid
            {224, 32,  16, 16},
            {240, 32,  16, 16},

            {96,  48,  16, 16}, // life p1

            {112, 48,  16, 16}, // life p2

            {0,   160, 16, 16}, // Explosion
            {16,  160, 16, 16},
            {32,  160, 16, 16},

            {0,   192, 16, 16}, // p1 shoot
            {16,  192, 16, 16},
            {32,  192, 16, 16},
            {48,  192, 16, 16},

            {64,  192, 16, 16}, // p2 shoot
            {80,  192, 16, 16},
            {96,  192, 16, 16},
            {112, 192, 16, 16},

            {128, 128, 32, 32}, // mine explosion
            {160, 128, 32, 32},
            {192, 128, 32, 32},

            {144, 72,  32, 24}, // space station h

            {16,  88,  40, 16},  // space station v

            {144, 48,  32, 24}, // h normal n
            {176, 64,  16, 16}, // ne
            {176, 88,  16, 16}, // se
            {144, 96,  32, 24}, // s
            {128, 88,  16, 16}, // sw
            {128, 64,  16, 16}, // nw

            {208, 56,  32, 16}, // h explode n
            {240, 64,  16, 16}, // ne
            {240, 88,  16, 16}, // se
            {208, 96,  32, 16}, // s
            {192, 88,  16, 16}, //sw
            {192, 64,  16, 16}, //nw

            {0,   88,  16, 16}, //  v normal w
            {8,   64,  24, 24}, //  nw
            {40,  64,  24, 24}, //  ne
            {56,  88,  16, 16}, // e
            {40,  104, 24, 24}, // se
            {8,   104, 24, 24}, // sw

            {72,  88,  8,  16}, // v explode w
            {72,  64,  24, 24}, // nw
            {104, 64,  24, 24}, // ne
            {120, 88,  8,  16}, // e
            {104, 104,  24, 24},  // se
            {72,  104,  24, 24}, // sw


            {48,  160, 32, 32}, // space station explosion
            {80, 160, 32, 32},
            {112, 160, 32, 32},
            {5, 237, 2, 2}, // player cursor
            {28, 240, 4, 4}, // spaceship cursor





    };

    std::vector<SDL_Rect> get_player_sprites() const;

    std::vector<SDL_Rect> get_e_type(bool leader = false) const;

    std::vector<SDL_Rect> get_i_type(bool leader = false) const;

    std::vector<SDL_Rect> get_p_type(bool leader = false) const;

    std::vector<SDL_Rect> get_spy() const;

    SDL_Rect get_mine() const;

    SDL_Rect get_asteroid(const unsigned int& sprite = 0) const;

    SDL_Rect get_p1_life() const;

    SDL_Rect get_p2_life() const;

    std::vector<SDL_Rect> get_explosion_1() const;

    std::vector<SDL_Rect> get_p1_shoot() const;

    std::vector<SDL_Rect> get_p2_shoot() const;

    std::vector<SDL_Rect> get_mine_explosion() const;

    std::vector<SDL_Rect> get_space_station_explosion() const;

    SDL_Rect get_space_station_h_core() const;

    SDL_Rect get_space_station_v_core() const;

    SDL_Rect get_cannon_hnn() const;

    SDL_Rect get_cannon_hnne() const;

    SDL_Rect get_cannon_hnse() const;

    SDL_Rect get_cannon_hns() const;

    SDL_Rect get_cannon_hnsw() const;

    SDL_Rect get_cannon_hnnw() const;

    SDL_Rect get_cannon_hen() const;

    SDL_Rect get_cannon_hene() const;

    SDL_Rect get_cannon_hese() const;

    SDL_Rect get_cannon_hes() const;

    SDL_Rect get_cannon_hesw() const;

    SDL_Rect get_cannon_henw() const;

    SDL_Rect get_cannon_vnw() const;

    SDL_Rect get_cannon_vnnw() const;

    SDL_Rect get_cannon_vnne() const;

    SDL_Rect get_cannon_vne() const;

    SDL_Rect get_cannon_vnse() const;

    SDL_Rect get_cannon_vnsw() const;

    SDL_Rect get_cannon_vew() const;

    SDL_Rect get_cannon_venw() const;

    SDL_Rect get_cannon_vene() const;

    SDL_Rect get_cannon_vee() const;

    SDL_Rect get_cannon_vese() const;

    SDL_Rect get_cannon_vesw() const;

    SDL_Rect get_player_cursor() const;

    SDL_Rect get_station_cursor() const;


    void render_background(const Player& player);

    void render_e_type(const Enemy& object);

    void render_p_type(const Enemy& object);

    void render_i_type(const Enemy& object);

    void render_spy(const Enemy& object);

    void update_screen();

    void render_side_bar(const Player& player, const std::vector<SpaceStation> stations);

    void render_player(const Player& object);

    void render_asteroid(const GameObject& object);

    void render_mine(const Mine& object);

    void render_space_station(const SpaceStation& object);

    void render_bullet(const Bullet& bullet);

    void render_animations();

    void render_collision_box(const GameObject& game_object);

    void load_sprite_sheet();

    void clear_screen();

    void update_camera(const Player* player);


public:

    Renderer();

    ~Renderer();

    void set_level(const Level* level);

    void update();

    void clear();



};










#endif