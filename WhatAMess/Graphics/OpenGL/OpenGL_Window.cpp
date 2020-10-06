#ifdef OPEN_GL_BUILD
#include "OpenGL_Window.h"
#include "../Window.h"

#include <iostream>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window::Instance().SetSize(width, height);
}

bool OpenGL_Window::Init(const int width, const int height, const char *windowTitle)
{
    this->width = width;
    this->height = height;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // glfw window creation
    // --------------------
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

bool OpenGL_Window::IsRunning()
{
    return !glfwWindowShouldClose(window);
}

void OpenGL_Window::Close()
{
    glfwSetWindowShouldClose(window, true);
}

void OpenGL_Window::CleanUp()
{
    glfwTerminate();
}

void OpenGL_Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void OpenGL_Window::PullEvents()
{
    glfwPollEvents();
}

bool OpenGL_Window::IsKeyPressed(KeyCode keyCode)
{
    return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

int OpenGL_Window::GetWidth()
{
    return width;
}

int OpenGL_Window::GetHeight()
{
    return height;
}

void OpenGL_Window::SetSize(const int width, const int height)
{
    this->width = width;
    this->height = height;
}

#endif
