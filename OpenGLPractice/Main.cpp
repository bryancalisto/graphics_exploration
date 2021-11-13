#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*Create a 800x800 pixel window with title 'OpenGL Practice'*/
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Practice", NULL, NULL);

	if (window == NULL) {
		std::cout << "Couldn't create window";
		glfwTerminate();
		return -1;
	}

	/*Associate this window to the current context*/
	glfwMakeContextCurrent(window);

	/*Ask GLAD to prepare openGL for us*/
	gladLoadGL();

	/*Tell openGL that the viewport starts at x=0 and y=0, and goes until x=800 and y=800*/
	glViewport(0, 0, 800, 800);

	/*Create a vertex shader*/
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	/*Create a fragment shader*/
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/*Create the shader program*/
	GLuint shaderProgram = glCreateProgram();

	/*Associate the shader program to the previously created shaders*/
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	/*Tell openGL about the program*/
	glLinkProgram(shaderProgram);

	/*Delete the shaders*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//Vertices for a equilateral triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
			0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
			0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
			-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
			0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
			0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	//GLuint indices[] = {
	//	0, 3, 5, // lower left triangle
	//	3, 2, 4, // lower right triangle
	//	5, 4, 1 // top triangle
	//};

	GLuint indices[] = {
		1, 5, 4, // lower left triangle
		4, 2, 3, // lower right triangle
		3, 0, 5, // top triangle
		1, 2, 5 // big triangle
	};

	/*Create references for the Vertex array object, vertex buffer object*/
	GLuint VAO, VBO, EBO;

	/*Generate the Vertex array object, vertex buffer object*/
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	/*Make the VAO the current vertex by binding it*/
	glBindVertexArray(VAO);

	/*Bind the VBO especifying it's a GL_ARRAY_BUFFER*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/*Put the vertices coordinates into the VBO*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*Bind another buffer object for the inner triangle*/
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*Configure the vertex attribute so that openGL knows how to interpret the VBO*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	/*Enable the vertex attribute so that openGL knows how to use it*/
	glEnableVertexAttribArray(0);

	/*Bind VAO and VBO to 0 so that we don't accidentally modify them */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Run until window is closed
	while (!glfwWindowShouldClose(window)) {
		// Specify color in background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell openGL to use the custom shader program we created
		glUseProgram(shaderProgram);
		// Bind the vao so openGL know how to use it
		glBindVertexArray(VAO);
		/*Tell openGL what to draw*/
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		/*Make the changes visible*/
		glfwSwapBuffers(window);
		// Poll for events every iteration
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}