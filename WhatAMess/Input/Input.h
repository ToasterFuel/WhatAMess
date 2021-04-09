#ifndef __INPUT_H__
#define __INPUT_H__

#include "KeyCode.h"
#include "MouseCode.h"
#include "../Graphics/Window.h"

class Input
{
public:
    static bool IsKeyPressed(KeyCode keyCode)
    {
        return Window::Instance().IsKeyPressed(keyCode);
    }

    static bool IsMouseButtonPressed(MouseCode mouseCode)
    {
        return Window::Instance().IsMouseButtonPressed(mouseCode);
    }

    /*
     * Returns the pixel the mouse cursor is at. (0, 0) is at the top left.
     */
    static glm::vec2 GetMouseScreenPosition()
    {
        return Window::Instance().GetMouseScreenPosition();
    }
};

#endif
