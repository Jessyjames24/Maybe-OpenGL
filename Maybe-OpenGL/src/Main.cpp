#include <iostream>

#include "glad/gl.h"
#include <GLFW\glfw3.h>
//#include "linmath.h"

#include "headers/Shader.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
const char* fragmentShaderSource = "#version 460 core\n"
	"out vec4 FragColor;\n"
	"in vec3 ourColour;\n"
	"void main(){\n"
	"	FragColor = vec4(ourColour, 1.0);\n"
	"}\n";


float vertices[]
{
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[] =
{
	0, 1, 2,
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Maybe OpenGL: InDev 0.0", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR: Window creation was unsuccessful!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cout << "ERROR: Unable to intialize GLAD\n";
		return -1;
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	glfwSwapInterval(1);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	/* 
	* 
		Vertex Buffer Object: used for storing vertices in a buffer. The VBO is then going to be used by the shader to
		understand how to draw (?)
	*
	*/
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*
	Determines how the data in the VBO (that came from float[] vertices) is layed out
	In this case: 3 floats in each vertex followed by...
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
	glEnableVertexAttribArray(0);
	// 3 floats for the colour of each vertex
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * (sizeof(float))));
	glEnableVertexAttribArray(1);
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.5f, 0.0f, 1.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		Shader shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");

		shader.Use();

		shader.SetFloat("offset", 0.5f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, (sizeof(indices) / (sizeof(int))), GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}