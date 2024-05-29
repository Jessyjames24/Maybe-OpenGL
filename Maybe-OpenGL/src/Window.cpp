#include <iostream>

#include "glad/gl.h"

#include "headers/Window.h"

Window::Window(int width, int height, std::string windowName)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_WindowID = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
	if (!m_WindowID)
	{
		std::cout << "ERROR: Window creation was unsuccessful!\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_WindowID);

	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cout << "ERROR: Unable to intialize GLAD\n";
	}

	glViewport(0, 0, width, height);
	
	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(m_WindowID);
	glfwTerminate();
}

GLFWwindow* Window::GetWindowID()
{
	return m_WindowID;
}
