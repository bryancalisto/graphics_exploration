#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

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



	//Vertices for a equilateral triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
			0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
			0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,// Upper corner
			-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,// Inner left
			0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,// Inner right
			0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,// Inner down
	};

	GLuint indices[] = {
		0, 3, 5, // lower left triangle
		3, 2, 4, // lower right triangle
		5, 4, 1 // top triangle
	};

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof vertices);
	EBO EBO1(indices, sizeof indices);

	VAO1.LinkVBO(VBO1, 0);

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Run until window is closed
	while (!glfwWindowShouldClose(window)) {
		// Specify color in background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean back buffer and assign new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		VAO1.Bind();

		/*Tell openGL what to draw*/
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		/*Make the changes visible*/
		glfwSwapBuffers(window);
		// Poll for events every iteration
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}