/*
* TODO:
* 2a) Put vert/frag shader in the same file to read in
* 2b) Don't use glm for setting values in the shader

* 5) Create a time object that handles timing/delta timings
* 6) How do you want to handle global singletons like Timings/Window?
*/
#include "Game/Game.h"

int main()
{
    Game game;
    if(!game.Init())
    {
        game.CleanUp();
        return -1;
    }
    if(!game.Run())
    {
        game.CleanUp();
        return -1;
    }

    game.CleanUp();
    return 0;
}
