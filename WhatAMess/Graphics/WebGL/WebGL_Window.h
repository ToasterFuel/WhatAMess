#ifndef __WEB_GL_WINDOW_H__
#define __WEB_GL_WINDOW_H__

#ifdef WEB_GL_BUILD

#include "../../Input/KeyCode.h"

#include <SDL.h>

class WebGL_Window
{
public:
    bool Init(int width, int height, const char *windowTitle);
    bool IsRunning();
    void Close();
    void Clear();
    void CleanUp();
    void SwapBuffers();
    void PullEvents();
    bool IsKeyPressed(KeyCode keyCode);
    int GetWidth();
    int GetHeight();

private:
    SDL_Window* window;
    int width;
    int height;
    void SetSize(const int width, const int height);
    friend class Window;
};
#endif
#endif
