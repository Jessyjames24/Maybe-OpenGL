
#include <iostream>

#include "glad/gl.h"
#include <GLFW\glfw3.h>
//#include "linmath.h"

#include "headers/Shader.h"
#include "headers/Window.h"

static float xOffset, yOffset;

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		yOffset += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		xOffset += -0.05f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		yOffset += -0.05f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		xOffset += 0.05f;
}

float vertices[]
{
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[] =
{
	0, 1, 2
};

int main() {
	Window window(800, 600, "Maybe OpenGL Indev 0.0");

	glfwSetFramebufferSizeCallback(window.GetWindowID(), FramebufferSizeCallback);

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

	Shader shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");

	while (!glfwWindowShouldClose(window.GetWindowID()))
	{
		ProcessInput(window.GetWindowID());

		glClearColor(0.5f, 0.0f, 1.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		shader.SetFloat("xOffset", xOffset);
		shader.SetFloat("yOffset", yOffset);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, (sizeof(indices) / (sizeof(int))), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window.GetWindowID());
		glfwPollEvents();
	}

}
