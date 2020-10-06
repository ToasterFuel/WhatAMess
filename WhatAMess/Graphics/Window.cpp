#include "Window.h"

Window::Window(): actualWindow()
{
}

bool Window::Init(const int width, const int height, const char *windowTitle)
{
    return actualWindow.Init(width, height, windowTitle);
}

bool Window::IsRunning()
{
    return actualWindow.IsRunning();
}

void Window::Close()
{
    actualWindow.Close();
}

void Window::CleanUp()
{
    actualWindow.CleanUp();
}

void Window::SwapBuffers()
{
    actualWindow.SwapBuffers();
}

void Window::PullEvents()
{
    actualWindow.PullEvents();
}

int Window::GetWidth()
{
    return actualWindow.GetWidth();
}

int Window::GetHeight()
{
    return actualWindow.GetHeight();
}

bool Window::IsKeyPressed(KeyCode keyCode)
{
    return actualWindow.IsKeyPressed(keyCode);
}

void Window::SetSize(const int width, const int height)
{
    actualWindow.SetSize(width, height);
}
