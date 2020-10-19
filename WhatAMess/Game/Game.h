#ifndef __GAME_H__
#define __GAME_H__

#ifdef OPEN_GL_BUILD
#include "OpenGL/OpenGL_Game.h"
#endif

class Game
{
public:
    Game();
    bool Init();
    bool Run();
    void CleanUp();

private:
    OpenGL_Game actualGame;
};

#endif
