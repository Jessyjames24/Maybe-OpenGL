#pragma once

#include "GLFW/glfw3.h"

#include <string>

class Window
{
public:
	Window(int width, int height, std::string windowName);
	~Window();

	GLFWwindow* GetWindowID();
private:
	GLFWwindow* m_WindowID;
	
};