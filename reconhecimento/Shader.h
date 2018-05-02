#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
private:
	GLuint program;
public:
	// Constructor generates the shader on the fly
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	GLuint getProgram();
	// Uses the current shader
	void use();
	~Shader();
};

