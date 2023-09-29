#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <SDL2/SDL.h>
#include "Player.h"
#include "Renderer.h"
#include "Vector2.h"


class GameHandler
{
private:
    Player player;
    Renderer renderer{};

public:
    GameHandler();

    void run();

};






#endif