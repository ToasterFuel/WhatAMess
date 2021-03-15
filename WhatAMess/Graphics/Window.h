#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "../Input/KeyCode.h"

#ifdef OPEN_GL_BUILD
#include "OpenGL/OpenGL_Window.h"
#elif WEB_GL_BUILD
#include "WebGL/WebGL_Window.h"
#endif

#define DEFAULT_WIDTH 1066
#define DEFAULT_HEIGHT 600

class Window
{
public:
    Window();
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
    /*
     * Note: This does not actually set the size of the window but just the internal storage of the width and height variables.
     */
    void SetSize(const int width, const int height);

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
};
#endif
