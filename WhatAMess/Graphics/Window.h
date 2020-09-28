#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    bool Init(int width, int height, const char *windowTitle);
    bool IsRunning();
    void Close();
    void CleanUp();
    void SwapBuffers();
    void PullEvents();
    GLFWwindow* GetWindow();
    int GetWidth();
    int GetHeight();

    static Window& Instance()
    {
        static Window instance;
        return instance;
    }

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        Window::Instance().SetSize(width, height);
    }

    /*
protected:
    Window(); // Prevent construction
    Window(const Window&); // Prevent construction by copying
    Window& operator=(const Window&); // Prevent assignment
    ~Window(); // Prevent unwanted destruction
    */

private:
    int width;
    int height;
    GLFWwindow* window;
    void SetSize(int width, int height);
};
#endif
