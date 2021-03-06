#ifdef OPEN_GL_BUILD
#include "OpenGL_Window.h"
#include "../Window.h"
#include "../../Input/OpenGL/OpenGL_Input.h"

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

    if(!OpenGL_Input::Init())
    {
        std::cout << "Failed to initialize OpenGL input\n";
        glfwTerminate();
        return false;
    }

    glfwSetMouseButtonCallback(window, OpenGL_Input::MouseButtonCallback);

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

void OpenGL_Window::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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

bool OpenGL_Window::IsMouseButtonPressed(MouseCode mouseCode)
{
    //Keeping around the query way of checking for mouse press because why not?
    //return glfwGetMouseButton(window, mouseCode) == GLFW_PRESS;
    return OpenGL_Input::IsMouseButtonPressed(mouseCode);
}

glm::vec2 OpenGL_Window::GetMouseScreenPosition()
{
    double x = 0;
    double y = 0;
    glfwGetCursorPos(window, &x, &y);

    return glm::vec2((float)x, (float)y);
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
