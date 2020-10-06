#ifndef __OPEN_GL_WINDOW_H__
#define __OPEN_GL_WINDOW_H__

#ifdef OPEN_GL_BUILD

#include "../../Input/KeyCode.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGL_Window
{
public:
    bool Init(int width, int height, const char *windowTitle);
    bool IsRunning();
    void Close();
    void CleanUp();
    void SwapBuffers();
    void PullEvents();
    bool IsKeyPressed(KeyCode keyCode);
    int GetWidth();
    int GetHeight();

private:
    int width;
    int height;
    GLFWwindow* window;
    void SetSize(const int width, const int height);
    friend class Window;
};

#endif
#endif
