#ifndef __OPEN_GL_WINDOW_H__
#define __OPEN_GL_WINDOW_H__

#ifdef OPEN_GL_BUILD

#include "../../Input/KeyCode.h"
#include "../../Input/MouseCode.h"

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGL_Window
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
    bool IsMouseButtonPressed(MouseCode mouseCode);
    glm::vec2 GetMouseScreenPosition();
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
