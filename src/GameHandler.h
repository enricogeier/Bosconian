#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H


#include "Input.h"
#include "Level.h"


class GameHandler
{
private:
     Renderer renderer;
     Vector2 keyboard_input_vector;
     Level level;
     Input input;

public:

   GameHandler() = default;

   void run();

};


#endif