#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "FPSTimer.h"
#include "Input.h"
#include "Level.h"


class GameHandler
{
private:
     Renderer renderer;
     Vector2 keyboard_input_vector;
     bool quit_game = false;
     FPSTimer fps_timer;
     long frame_counter = 1;
     Level level;
     Input input;


    void render();



public:

   GameHandler() = default;

   void run();

};


#endif