#include"shaderClass.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);

	if (!in) {
		std::cout << "ERROR READING FILE" << std::endl;
	}

	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();
	return contents;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents("default.vert");
	std::string fragmentCode = get_file_contents("default.frag");

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	/*Create a vertex shader*/
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	CompileErrors(vertexShader, "VERTEX");

	/*Create a fragment shader*/
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	CompileErrors(fragmentShader, "FRAGMENT");

	/*Create the shader program*/
	ID = glCreateProgram();

	/*Associate the shader program to the previously created shaders*/
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	/*Tell openGL about the program*/
	glLinkProgram(ID);
	CompileErrors(ID, "PROGRAM");

	/*Delete the shaders*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	// Tell openGL to use the custom shader program we created
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::CompileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER COMPILATION ERROR FOR: " << type << std::endl;
		}
		else {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER LINKING ERROR FOR: " << type << std::endl;
		}
	}
}
