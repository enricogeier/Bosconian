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

    /**
     * Constructs a new GameHandler object. Controller instance of the program.
     */
   GameHandler() = default;

   /**
    * Runs the game. Initializes Model and View properties
    */
   void run();

};


#endif