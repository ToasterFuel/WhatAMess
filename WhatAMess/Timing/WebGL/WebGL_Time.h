#ifndef __WEB_GL_TIME__
#define __WEB_GL_TIME__

#ifdef WEB_GL_BUILD

class WebGL_Time
{
public:
    WebGL_Time();
    void CalculateDeltaTime();
    /*
    * Time is in seconds.
    */
    float DeltaTime();
private:
    unsigned int lastTime;
    unsigned int currentTime;
    float deltaTime;
};

#endif

#endif
