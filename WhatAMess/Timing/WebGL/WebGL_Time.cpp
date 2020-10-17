#ifdef WEB_GL_BUILD
#include "WebGL_Time.h"

//#include <SDL.h>
#include <SDL2/SDL.h>

WebGL_Time::WebGL_Time() : lastTime(0), currentTime(0), deltaTime(0)
{
}

void WebGL_Time::CalculateDeltaTime()
{
    currentTime = SDL_GetTicks();
    deltaTime = (float)(currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
}

/*
* Time is in seconds.
*/
float WebGL_Time::DeltaTime()
{
    return deltaTime;
}
#endif