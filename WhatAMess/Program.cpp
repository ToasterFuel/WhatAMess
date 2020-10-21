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
