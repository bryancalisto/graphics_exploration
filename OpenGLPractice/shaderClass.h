#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	// Reference to the shader program
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);
	// Activates the shader program
	void Activate();
	// Deletes the shader program
	void Delete();

	void CompileErrors(unsigned int shader, const char* type);
};
