#ifndef __TIME_H__
#define __TIME_H__

#ifdef OPEN_GL_BUILD
#include "OpenGL/OpenGL_Time.h"
#elif WEB_GL_BUILD
#include "WebGL/WebGL_Time.h"
#endif


class Time
{
public:
    Time();
    void CalculateDeltaTime();
    /*
     * Time is in seconds.
     */
    float DeltaTime();

    static Time& Instance()
    {
        static Time instance;
        return instance;
    }
private:
#ifdef OPEN_GL_BUILD
    OpenGL_Time actualTime;
#elif WEB_GL_BUILD
    WebGL_Time actualTime;
#endif
};

#endif