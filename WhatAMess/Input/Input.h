#ifndef __INPUT_H__
#define __INPUT_H__

#include "KeyCode.h"
#include "../Graphics/Window.h"

class Input
{
public:
    static bool IsKeyPressed(KeyCode keyCode)
    {
        return Window::Instance().IsKeyPressed(keyCode);
    }
};

#endif