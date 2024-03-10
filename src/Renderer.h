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

    /**
     * Constructs a new AnimationPlayer object.
     *
     * @param explosion_sprites Sprite values to depict.
     * @param game_object Reference to GameObject instance which animation is assigned to.
     */
    AnimationPlayer(std::vector<SDL_Rect> explosion_sprites, GameObject& game_object)
    : position(game_object.position), id(game_object.id), scale(game_object.scale), frame_time(std::chrono::microseconds(0))
    {
        this->explosion_sprites = std::move(explosion_sprites);
        frame_time = std::chrono::duration_cast<std::chrono::microseconds>(duration / this->explosion_sprites.size());

    }

    /**
     * Constructs a new AnimationPlayer object.
     *
     * @param explosion_sprites Sprite values to depict.
     * @param game_object Reference to GameObject instance which animation is assigned to.
     * @param duration Duration of animation in microseconds.
     */
    AnimationPlayer(std::vector<SDL_Rect> explosion_sprites, GameObject& game_object, std::chrono::microseconds duration)
            : position(game_object.position), id(game_object.id), scale(game_object.scale),
            frame_time(std::chrono::microseconds(0)), duration(duration)
    {
        this->explosion_sprites = std::move(explosion_sprites);
        frame_time = std::chrono::duration_cast<std::chrono::microseconds>(duration / this->explosion_sprites.size());

    }

    /**
     * Constructs a new AnimationPlayer object.
     *
     * @param explosion_sprites Sprite values to depict.
     * @param position position of animation in game
     * @param id animation id to distinguish.
     * @param scale value which describes the scale of each sprite.
     */
    AnimationPlayer(std::vector<SDL_Rect> explosion_sprites, Vector2& position, const unsigned int& id, const Vector2& scale)
    : position(position), id(id), scale(scale), frame_time(std::chrono::microseconds(0))
    {
        this->explosion_sprites = std::move(explosion_sprites);
        frame_time = std::chrono::duration_cast<std::chrono::microseconds>(duration / this->explosion_sprites.size());
    }

    /**
     * Plays and handles the animation.
     *
     * @return Reference containing information about current sprite in animation.
     */
    SDL_Rect* get_animation_sprite();


    Vector2 scale = Vector2(1.0f, 1.0f);
};


class Renderer
{
private:

    const int SCREEN_SIZE_WIDTH = 1920;   // small: 960
    const int SCREEN_SIZE_HEIGHT = 1080; // 540

    const Vector2 SCALE = Vector2(4.0f, 4.0f);

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


    std::vector<SDL_Rect> particles;
    std::chrono::microseconds point_timer = std::chrono::microseconds(0);
    const uint16_t NUM_PARTICLES = 500;  // default: 300

    const int GRID_SIZE_X = 4;
    const int GRID_SIZE_Y = 4;

    std::vector<SDL_Color> colors = {
            {255, 0, 0},
            {0, 255, 0},
            {0, 0, 255},
            {255, 255, 0},
            {255, 0, 255},
            {0, 255, 255}
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
            {64, 240, 61, 7}, // hi-score
            {1, 208, 8, 7}, // 0
            {10, 208, 7, 7}, // 1
            {17, 208, 8, 7}, // 2
            {25, 208, 8, 7}, // 3
            {33, 208, 8, 7}, // 4
            {41, 208, 8, 7}, // 5
            {49, 208, 8, 7}, // 6
            {57, 208, 8, 7}, // 7
            {65, 208, 8, 7}, // 8
            {73, 208, 8, 7}, // 9
            {64, 224, 22, 7}, // 1UP
            {128, 208, 64, 7}, // condition
            {64, 249, 37, 7}, // green
            {64, 233, 39, 7}, // round
            {144, 160, 64, 16}, // game over




    };

    /**
     * Retrieves player sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_player_sprites() const;

    /**
     * Retrieves e type sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_e_type(bool leader = false) const;

    /**
     * Retrieves i type sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_i_type(bool leader = false) const;

    /**
     * Retrieves p type sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_p_type(bool leader = false) const;

    /**
     * Retrieves spy sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_spy() const;

    /**
     * Retrieves mine sprite information.
     *
     * @return mine sprite information.
     */
    SDL_Rect get_mine() const;

    /**
     * Retrieves asteroid sprite information.
     *
     * @return asteroid sprite information.
     */
    SDL_Rect get_asteroid(const unsigned int& sprite = 0) const;

    /**
     * Retrieves p1 life sprite information.
     *
     * @return p1 life sprite information.
     */
    SDL_Rect get_p1_life() const;

    /**
     * Retrieves p2 life sprite information.
     *
     * @return p2 life sprite information.
     */
    SDL_Rect get_p2_life() const;

    /**
     * Retrieves explosion 1 sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_explosion_1() const;

    /**
     * Retrieves p1 shoot sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_p1_shoot() const;

    /**
     * Retrieves p2 shoot sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_p2_shoot() const;

    /**
     * Retrieves mine explosion sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_mine_explosion() const;

    /**
     * Retrieves space station explosion sprites information.
     *
     * @return list of information for each sprite.
     */
    std::vector<SDL_Rect> get_space_station_explosion() const;

    /**
     * Retrieves space station h core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_space_station_h_core() const;

    /**
     * Retrieves space station v core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_space_station_v_core() const;

    /**
     * Retrieves cannon hnn core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hnn() const;

    /**
     * Retrieves cannon hnne core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hnne() const;

    /**
     * Retrieves cannon hnse core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hnse() const;

    /**
     * Retrieves cannon hns core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hns() const;

    /**
     * Retrieves cannon hnsw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hnsw() const;

    /**
     * Retrieves cannon hnnw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hnnw() const;

    /**
     * Retrieves cannon hen core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hen() const;

    /**
     * Retrieves cannon hene core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hene() const;

    /**
     * Retrieves cannon hese core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hese() const;

    /**
     * Retrieves cannon hes core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hes() const;

    /**
     * Retrieves cannon hesw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_hesw() const;

    /**
     * Retrieves cannon henw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_henw() const;

    /**
     * Retrieves cannon vnw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vnw() const;

    /**
     * Retrieves cannon vnnw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vnnw() const;

    /**
     * Retrieves cannon vnne core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vnne() const;

    /**
     * Retrieves cannon vne core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vne() const;

    /**
     * Retrieves cannon vnse core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vnse() const;

    /**
     * Retrieves cannon vnsw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vnsw() const;

    /**
     * Retrieves cannon vew core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vew() const;

    /**
     * Retrieves cannon venw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_venw() const;

    /**
     * Retrieves cannon vene core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vene() const;

    /**
     * Retrieves cannon vee core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vee() const;

    /**
     * Retrieves cannon vese core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vese() const;

    /**
     * Retrieves cannon vesw core sprites information.
     *
     * @return list of information for each sprite.
     */
    SDL_Rect get_cannon_vesw() const;

    /**
     * Retrieve player cursor sprite information.
     *
     * @return player cursor sprite information.
     */
    SDL_Rect get_player_cursor() const;

    /**
    * Retrieve station cursor sprite information.
    *
    * @return station cursor sprite information.
    */
    SDL_Rect get_station_cursor() const;

    /**
    * Retrieve high score sprite information.
    *
    * @return high score sprite information.
    */
    SDL_Rect get_hi_score() const;

    /**
    * Retrieve number sprite information.
    *
    * @return number sprite sprite information.
    */
    SDL_Rect get_number(char number) const;

    /**
    * Retrieve 1UP sprite information.
    *
    * @return 1UP sprite sprite information.
    */
    SDL_Rect get_1UP() const;

    /**
    * Retrieve condition sprite information.
    *
    * @return condition sprite sprite information.
    */
    SDL_Rect get_condition() const;

    /**
    * Retrieve green condition sprite information.
    *
    * @return green condition sprite sprite information.
    */
    SDL_Rect get_green() const;

    /**
    * Retrieve round sprite information.
    *
    * @return round sprite sprite information.
    */
    SDL_Rect get_round() const;

    /**
    * Retrieve game over sprite information.
    *
    * @return game over sprite sprite information.
    */
    SDL_Rect get_gameOver() const;

    /**
     * Renders background particles.
     *
     * @param player position of Player instance
     */
    void render_background(const Player& player);

    /**
     * Renders E Type sprite.
     *
     * @param object Enemy reference containing enemy information.
     */
    void render_e_type(const Enemy& object);

    /**
     * Renders P Type sprite.
     *
     * @param object Enemy reference containing enemy information.
     */
    void render_p_type(const Enemy& object);

    /**
     * Renders I Type sprite.
     *
     * @param object Enemy reference containing enemy information.
     */
    void render_i_type(const Enemy& object);

    /**
     * Renders spy sprite.
     *
     * @param object Enemy reference containing enemy information.
     */
    void render_spy(const Enemy& object);

    /**
     * Draws everything on the screen.
     */
    void update_screen();

    /**
     * Renders the side bar.
     *
     * @param player Player reference containing player information to show the Player cursor.
     * @param stations list of SpaceStation instances to show the SpaceStation Cursors.
     */
    void render_side_bar(const Player& player, const std::vector<SpaceStation> stations);

    /**
     * Renders the player.
     *
     * @param object Player reference containing player information.
     */
    void render_player(const Player& object);

    /**
     * Renders an asteroid.
     *
     * @param object GameObject reference containing asteroid information.
     */
    void render_asteroid(const GameObject& object);

    /**
     * Renders a mine.
     *
     * @param object Mine reference containing mine information.
     */
    void render_mine(const Mine& object);

    /**
     * Renders a space station and its cannons
     *
     * @param object SpaceStation reference containing space station and cannons information.
     */
    void render_space_station(const SpaceStation& object);

    /**
     * Renders a bullet.
     *
     * @param bullet Bullet reference containing bullet information.
     */
    void render_bullet(const Bullet& bullet);

    /**
     * Renders all animations in one frame.
     */
    void render_animations();

    /**
     * Renders a collision box assigned to a GameObject reference.
     * @param game_object GameObject reference containing object information.
     */
    void render_collision_box(const GameObject& game_object);

    /**
     * Loads the sprite sheet. Called when Renderer is initialized.
     */
    void load_sprite_sheet();

    /**
     * Clears the screen to further draw objects again.
     */
    void clear_screen();

    /**
     * Updates the camera based on the player's position.
     * @param player Player reference containing player information.
     */
    void update_camera(const Player* player);

    /**
     * Renders a given number backwards for the side bar.
     *
     * @param numbers Number to render.
     * @param sprites Sprites to use to render the number.
     * @param render_quad Render position on screen.
     * @param y_pos y Position of the number to render.
     * @param number_width width of the number to render. Default value is 53 if not provided.
     * @param number_height height of the number to render. Default value is 46 if not provided.
     */
    void render_number_backwards(std::string& numbers, SDL_Rect& sprites, SDL_Rect& render_quad, int y_pos,
                                 int number_width = 53, int number_height = 46);



public:

    /**
     * Constructs a new Renderer object. Represents the view.
     */
    Renderer();

    ~Renderer();

    /**
     * Sets the level attribute for read-only purposes.
     * @param level Level reference to read data from.
     */
    void set_level(const Level* level);

    /**
     * Update screen. Called every frame to draw on screen.
     */
    void update();

    /**
     * Clears the Renderer. Called if program will close.
     */
    void clear();



};










#endif