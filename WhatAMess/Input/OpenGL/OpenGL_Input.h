#ifndef __OPEN_GL_INPUT_H__
#define __OPEN_GL_INPUT_H__

#include <GLFW/glfw3.h>
#include "../MouseCode.h"

#include <iostream>

class OpenGL_Input
{
public:
	static bool Init()
	{
		for (int i = 0; i < MOUSE_COUNT; i++)
		{
			buttonsPressed[i] = false;
		}
		return true;
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if(button < 0 || button >= MOUSE_COUNT)
		{
			return;
		}
		buttonsPressed[button] = action == GLFW_PRESS;
	}

	static bool IsMouseButtonPressed(MouseCode mouseCode)
	{
		if(mouseCode < 0 || mouseCode >= MOUSE_COUNT)
			return false;

		return buttonsPressed[mouseCode];
	}


private:
	static bool buttonsPressed[MOUSE_COUNT];
};

#endif