#ifndef __WEB_GL_INPUT__
#define __WEB_GL_INPUT__

#ifdef WEB_GL_BUILD

#include <emscripten/html5.h>
#include <map>
#include <string.h>

#include "../KeyCode.h"

struct KeyState
{
    bool isPressed;
};

struct CompareString
{
   bool operator()(char const *a, char const *b) const
   {
      return std::strcmp(a, b) < 0;
   }
};

class WebGL_Input
{
public:
    static void Init()
    {
        for(int i = 0; i < KEY_LAST + 1; i++)
        {
            keyStates[i].isPressed = false;
        }
    }

    static bool IsKeyPressed(KeyCode keyCode)
    {
        if(keyCode == KEY_INVALID)
            return false;
        return keyStates[keyCode].isPressed;
    }

    static EM_BOOL KeyPressed(int eventType, const EmscriptenKeyboardEvent* event, void *userData)
    {
        KeyCode keyCode = GetKeyCodeFromString(event->code);
        if(keyCode == KEY_INVALID)
            return false;
        keyStates[keyCode].isPressed = true;

        return true;
    }

    static EM_BOOL KeyReleased(int eventType, const EmscriptenKeyboardEvent* event, void *userData)
    {
        KeyCode keyCode = GetKeyCodeFromString(event->code);
        if(keyCode == KEY_INVALID)
            return false;
        keyStates[keyCode].isPressed = false;
        return true;
    }

private:
    static KeyState keyStates[KEY_LAST + 1];
    static const std::map<const char*, KeyCode, CompareString> stringToKeyCode;

    static KeyCode GetKeyCodeFromString(const char* value)
    {
        auto iterator = stringToKeyCode.find(value);
        if(iterator == stringToKeyCode.end())
            return KEY_INVALID;

        return iterator->second;
    }
};

#endif

#endif
