#ifdef OPEN_GL_BUILD

#include "OpenGL_Game.h"
#include "../../Graphics/Window.h"
#include "../../Graphics/Camera.h"
#include "../../Timing/Time.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

OpenGL_Game::OpenGL_Game(): gameLogic()
{
}

bool OpenGL_Game::Init()
{
    if(!Window::Instance().Init(800, 600, "What A Mess"))
    {
        Window::Instance().CleanUp();
        return false;
    }
    stbi_set_flip_vertically_on_load(true);
    gameLogic.Init();
    return true;
}

bool OpenGL_Game::Run()
{
    while(Window::Instance().IsRunning())
    {
        Time::Instance().CalculateDeltaTime();
        Window::Instance().Clear();

        gameLogic.Update();

        Window::Instance().SwapBuffers();
        Window::Instance().PullEvents();
    }
    return true;
}

void OpenGL_Game::CleanUp()
{
    Window::Instance().CleanUp();
    gameLogic.CleanUp();
}

#endif
