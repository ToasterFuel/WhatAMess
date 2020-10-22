#ifndef __WEB_GL_GAME__
#define __WEB_GL_GAME__
#ifdef WEB_GL_BUILD

#include "../GameLogic.h"

class WebGL_Game
{
public:
    static WebGL_Game* instance;
    void Loop();

    WebGL_Game();
    bool Init();
    bool Run();
    void CleanUp();
private:
    GameLogic gameLogic;
};
#endif
#endif
