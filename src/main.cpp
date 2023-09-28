#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "stdio.h"
#include "vector2.h"
#include "Player.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The window renderer
SDL_Renderer* gRenderer = NULL;





// Starts up SDL and creates window
bool init()
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    // Create window
    gWindow = SDL_CreateWindow("Bosconian", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if(gWindow == NULL)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL)
    {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize renderer color. Set the color used for drawing operations (Rect, Line and Clear).
    // Set the color for drawing or filling rectangles, lines, and points, and for SDL_RenderClear().
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);


    return true;

}



// Frees media and shuts down SDL
void close()
{

    // Free loaded image
    /*
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    */

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    SDL_Quit();


}






int main(int argc, char* args[])
{

    if(!init())
    {
        return -1;
    }


    Player player(Vector2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Vector2(0.0f, -1.0f), 3, 0.125f, 0.0125f);


    // Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    bool input_change = false;

    while(!quit)
    {
        // Handle events on queue. SDL's internal keystates are updated every time SDL PollEvent is called
        while(SDL_PollEvent(&e)) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;

            }
            else if(e.type == SDL_KEYDOWN)
            {
                input_change = true;
            }

        }

        Vector2 new_position;
        Vector2 new_direction;

        if(input_change)
        {
            input_change = false;

            const Uint8* current_key_state =  SDL_GetKeyboardState(NULL);

            if(current_key_state[SDL_SCANCODE_UP])
            {
                new_direction.y = -1.0f;
            }
            if(current_key_state[SDL_SCANCODE_DOWN])
            {
                new_direction.y = 1.0f;
            }
            if(current_key_state[SDL_SCANCODE_LEFT])
            {
                new_direction.x = -1.0f;
            }
            if(current_key_state[SDL_SCANCODE_RIGHT])
            {
                new_direction.x = 1.0f;
            }


        }

        player.move(new_direction);




        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        player.render(gRenderer);


        // Update screen
        SDL_RenderPresent(gRenderer);

    }

    close();

    return 0;


}
