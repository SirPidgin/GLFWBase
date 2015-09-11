#include <GL/glew.h>					// Include GLEW...
#include <GL/glfw3.h>					// ...before GLFW!
#include <glm/glm.hpp>

#include "Shader.h"

int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "Tutorial", NULL, NULL);
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glViewport(0, 0, 1024, 768);

	//--------------------

	glewExperimental = true;		// So GLEW uses more modern techniques for managing OpenGL functionality.

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW!\n");
		return -1;
	}

	Shader ourShader("VertexShader.txt", "FragmentShader.txt");

	//--------------------

	GLfloat vertices[] =
	{
		0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,			// Top Right (3 positions, 3 colors)
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,			// Bottom Right (3 positions, 3 colors)
		-0.5f, -0.5f, 0.0f,	 0.0f, 0.0f, 1.0f,			// Bottom Left (3 positions, 3 colors)
		-0.5f, 0.5f, 0.0f,  0.5f, 0.0f, 0.5f			// Top Left (3 positions, 3 colors)
	};

	GLuint indices[] =
	{
		0, 1, 3,					// First Triangle
		1, 2, 3						// Second Triangle
	};

	GLuint vertexBufferObject, vertexArrayObject, elementBufferObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexBufferObject);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);				// Unbinds VAO

	//--------------------

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		GLfloat timeValue = glfwGetTime();
		GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.4f, 1.0f);

		glBindVertexArray(vertexArrayObject);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);

	glfwTerminate();
	return 0;
}