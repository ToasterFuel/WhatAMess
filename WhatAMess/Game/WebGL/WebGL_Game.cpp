#ifdef WEB_GL_BUILD
#include "WebGL_Game.h"
#include "../../Graphics/Window.h"
#include "../../Timing/Time.h"
#include "../../Input/WebGL/WebGL_Input.h"

#include <emscripten.h>
#include <emscripten/html5.h>

WebGL_Game::WebGL_Game(): gameLogic()
{
}

void WebGL_Game::Loop()
{
    Time::Instance().CalculateDeltaTime();
    Window::Instance().Clear();

    gameLogic.Update();

    Window::Instance().SwapBuffers();
    Window::Instance().PullEvents();
}

void MainLoop()
{
    WebGL_Game::instance->Loop();
}

bool WebGL_Game::Init()
{
    instance = this;
    Window::Instance().Init(800, 600, "");
    gameLogic.Init();

    emscripten_set_keydown_callback("#canvas", nullptr, true, WebGL_Input::KeyPressed);
    emscripten_set_keyup_callback("#canvas", nullptr, true, WebGL_Input::KeyReleased);
    emscripten_set_main_loop(MainLoop, 0, true);

    return true;
}

bool WebGL_Game::Run()
{
    return true;
}

void WebGL_Game::CleanUp()
{
}
#endif
