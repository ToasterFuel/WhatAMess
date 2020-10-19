#include "Game.h"

Game::Game(): actualGame()
{
}

bool Game::Init()
{
    return actualGame.Init();
}

bool Game::Run()
{
    return actualGame.Run();
}

void Game::CleanUp()
{
    actualGame.CleanUp();
}
