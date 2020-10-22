#ifndef __GAME_H__
#define __GAME_H__

#ifdef OPEN_GL_BUILD
#include "OpenGL/OpenGL_Game.h"
#elif WEB_GL_BUILD
#include "WebGL/WebGL_Game.h"
#endif

class Game
{
public:
    Game();
    bool Init();
    bool Run();
    void CleanUp();

private:
#ifdef OPEN_GL_BUILD
    OpenGL_Game actualGame;
#elif WEB_GL_BUILD
    WebGL_Game actualGame;
#endif
};

#endif
