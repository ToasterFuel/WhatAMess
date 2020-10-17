#ifndef __OPEN_GL_TIME__
#define __OPEN_GL_TIME__

#ifdef OPEN_GL_BUILD

class OpenGL_Time
{
public:
    OpenGL_Time();
    void CalculateDeltaTime();
    /*
    * Time is in seconds.
    */
    float DeltaTime();
private:
    double lastTime;
    double currentTime;
    float deltaTime;
};

#endif
#endif
