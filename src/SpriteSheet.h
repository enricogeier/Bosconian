#ifndef SPRITESHEET_H
#define SPRITESHEET_H


#include <string>
#include <vector>
#include <iostream>
#include "Player.h"

class SpriteSheet
{

public:
    const static int SPRITE_SHEET_WIDTH = 256;
    const static int SPRITE_SHEET_HEIGHT = 400;
    const static std::string PATH_TO_SPRITE_SHEET;

    // constexpr: value is known at compile-time => for compiler
    constexpr static Rectangle sprites[256] = {
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



    static std::vector<Rectangle> get_player_sprites()
    {
        std::vector<Rectangle> sprite_list;

        sprite_list.push_back(sprites[0]);
        sprite_list.push_back(sprites[1]);

        return sprite_list;

    }

    static std::vector<Rectangle> get_e_type(bool leader = false)
    {
        std::vector<Rectangle> sprite_list;

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

    static std::vector<Rectangle> get_i_type(bool leader = false)
    {
        std::vector<Rectangle> sprite_list;

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

    static std::vector<Rectangle> get_p_type(bool leader = false)
    {
        std::vector<Rectangle> sprite_list;

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

    static std::vector<Rectangle> get_spy()
    {
        std::vector<Rectangle> sprite_list;

        sprite_list.push_back(sprites[38]);
        sprite_list.push_back(sprites[39]);
        sprite_list.push_back(sprites[40]);
        sprite_list.push_back(sprites[41]);
        sprite_list.push_back(sprites[42]);
        sprite_list.push_back(sprites[43]);

        return sprite_list;

    }

    static Rectangle get_mine()
    {
        return sprites[44];
    }

    static Rectangle get_asteroid(short sprite = 0)
    {
        if(sprite >= 0 && sprite < 3)
        {
            return sprites[45 +  sprite];
        }
        else
        {
            std::cerr << "wrong sprite number for get_asteroid()" << std::endl;
        }
    }

    static Rectangle get_p1_life()
    {
        return sprites[48];
    }

    static Rectangle get_p2_life()
    {
        return sprites[49];
    }

    static std::vector<Rectangle> get_explosion_1()
    {
        std::vector<Rectangle> sprite_list;

        sprite_list.push_back(sprites[50]);
        sprite_list.push_back(sprites[51]);
        sprite_list.push_back(sprites[52]);

        return sprite_list;
    }

    static std::vector<Rectangle> get_p1_shoot()
    {
        std::vector<Rectangle> sprite_list;

        sprite_list.push_back(sprites[53]);
        sprite_list.push_back(sprites[54]);
        sprite_list.push_back(sprites[55]);
        sprite_list.push_back(sprites[56]);

        return sprite_list;
    }

    static std::vector<Rectangle> get_p2_shoot()
    {
        std::vector<Rectangle> sprite_list;

        sprite_list.push_back(sprites[57]);
        sprite_list.push_back(sprites[58]);
        sprite_list.push_back(sprites[59]);
        sprite_list.push_back(sprites[60]);

        return sprite_list;
    }


};

#endif
