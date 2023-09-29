#include "GameHandler.h"

GameHandler::GameHandler()
{
    player = Player(Vector2(640 / 2, 480 / 2), Vector2(0.0f, -1.0f), 3, 0.125f, 0.0125f);

}

void GameHandler::run()
{
    if(!renderer.initialize())
    {
        return;
    }


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

        Vector2 keyboard_input_vector;

        if(input_change)
        {
            input_change = false;

            const Uint8* current_key_state =  SDL_GetKeyboardState(NULL);

            if(current_key_state[SDL_SCANCODE_UP])
            {
                keyboard_input_vector.y = -1.0f;
            }
            if(current_key_state[SDL_SCANCODE_DOWN])
            {
                keyboard_input_vector.y = 1.0f;
            }
            if(current_key_state[SDL_SCANCODE_LEFT])
            {
                keyboard_input_vector.x = -1.0f;
            }
            if(current_key_state[SDL_SCANCODE_RIGHT])
            {
                keyboard_input_vector.x = 1.0f;
            }


        }

        player.move(keyboard_input_vector);

        renderer.render_player(player);


    }

    renderer.clear();



}