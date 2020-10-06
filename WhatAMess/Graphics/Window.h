#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "../Input/KeyCode.h"

#ifdef OPEN_GL_BUILD
#include "OpenGL/OpenGL_Window.h"
#elif WEB_GL_BUILD
#include "WebGL/WebGL_Window.h"
#endif

class Window
{
public:
    Window();
    bool Init(int width, int height, const char *windowTitle);
    bool IsRunning();
    void Close();
    void CleanUp();
    void SwapBuffers();
    void PullEvents();
    bool IsKeyPressed(KeyCode keyCode);
    int GetWidth();
    int GetHeight();

    static Window& Instance()
    {
        static Window instance;
        return instance;
    }

    /*
protected:
    Window(); // Prevent construction
    Window(const Window&); // Prevent construction by copying
    Window& operator=(const Window&); // Prevent assignment
    ~Window(); // Prevent unwanted destruction
    */
private:
#ifdef OPEN_GL_BUILD
    OpenGL_Window actualWindow;
    friend class OpenGL_Window;
#elif WEB_GL_BUILD
    WebGL_Window actualWindow;
    friend class WebGL_Window;
#endif
    void SetSize(const int width, const int height);
};
#endif
