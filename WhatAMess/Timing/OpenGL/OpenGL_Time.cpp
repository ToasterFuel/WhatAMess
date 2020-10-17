#ifdef OPEN_GL_BUILD
#include "OpenGL_Time.h"

#include <GLFW/glfw3.h>

OpenGL_Time::OpenGL_Time(): lastTime(0), currentTime(0), deltaTime(0)
{
}

void OpenGL_Time::CalculateDeltaTime()
{
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
}

/*
* Time is in seconds.
*/
float OpenGL_Time::DeltaTime()
{
    return deltaTime;
}
#endif