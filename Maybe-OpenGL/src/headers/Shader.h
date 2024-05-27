#pragma once

#include "glad/gl.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragPath);
	~Shader();

	void Use();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value)const;
	void SetFloat(const std::string& name, float value)const;
	void ShaderCompilationCheck(unsigned int shader);
	void ShaderLinkingCheck(unsigned int program);
};