#include "Window.h"

#include <iostream>

bool Window::Init(const int width, const int height, const char *windowTitle)
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
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // glfw window creation
    // --------------------
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, Window::FramebufferSizeCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

bool Window::IsRunning()
{
    return !glfwWindowShouldClose(window);
}

void Window::Close()
{
    glfwSetWindowShouldClose(window, true);
}

void Window::CleanUp()
{
    glfwTerminate();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::PullEvents()
{
    glfwPollEvents();
}

GLFWwindow* Window::GetWindow()
{
    return window;
}

int Window::GetWidth()
{
    return width;
}

int Window::GetHeight()
{
    return height;
}

void Window::SetSize(int width, int height)
{
    this->width = width;
    this->height = height;
}
