#ifdef WEB_GL_BUILD
#include "WebGL_Window.h"
#include "../../Input/WebGL/WebGL_Input.h"

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_opengles2.h>

bool WebGL_Window::Init(const int width, const int height, const char *windowTitle)
{
    this->width = width;
    this->height = height;
    SDL_Window *window;
    SDL_CreateWindowAndRenderer(width, height, 0, &window, nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

bool WebGL_Window::IsRunning()
{
    //Game will always be running for WebGL
    return true;
}

void WebGL_Window::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void WebGL_Window::Close()
{
    //Don't need to close anything for WebGL
}

void WebGL_Window::CleanUp()
{
    SDL_DestroyWindow(window);
}

void WebGL_Window::SwapBuffers()
{
    SDL_GL_SwapWindow(window);
}

void WebGL_Window::PullEvents()
{
    //TODO: implement
    //glfwPollEvents();
}

bool WebGL_Window::IsKeyPressed(KeyCode keyCode)
{
    return WebGL_Input::IsKeyPressed(keyCode);
}

int WebGL_Window::GetWidth()
{
    return width;
}

int WebGL_Window::GetHeight()
{
    return height;
}

void WebGL_Window::SetSize(const int width, const int height)
{
    this->width = width;
    this->height = height;
}
#endif
