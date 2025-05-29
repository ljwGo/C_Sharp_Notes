#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

class MyShader
{
public:
	unsigned int programId;

	MyShader(std::string vertexShaderPath, std::string fragmentShaderPath);

	void SetUniform4f(std::string uName, float x, float y, float z, float w);

	void SetUniform1f(std::string uName, float val);

	void Use();

private:
	unsigned int CreateShader(GLenum shaderType, const char* src);

	void DeleteShader(unsigned int id);
};

