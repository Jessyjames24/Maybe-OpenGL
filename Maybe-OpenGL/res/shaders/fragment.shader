#version 460 core

out vec4 FragColor;
in vec3 ourColour;
in vec4 position;

void main()
{
	FragColor = vec4(ourColour, 1.0);
}