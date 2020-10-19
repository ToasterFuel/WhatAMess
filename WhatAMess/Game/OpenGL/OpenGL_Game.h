#ifndef __OPEN_GL_GAME__
#define __OPEN_GL_GAME__
#ifdef OPEN_GL_BUILD
#include "../GameLogic.h"

class OpenGL_Game
{
public:
    OpenGL_Game();
    bool Init();
    bool Run();
    void CleanUp();
private:
    GameLogic gameLogic;
};

#endif
#endif
