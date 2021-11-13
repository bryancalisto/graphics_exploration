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

	/*Create a fragment shader*/
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*Create the shader program*/
	ID = glCreateProgram();

	/*Associate the shader program to the previously created shaders*/
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	/*Tell openGL about the program*/
	glLinkProgram(ID);

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
