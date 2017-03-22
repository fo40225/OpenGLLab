// OpenGLLab.cpp : 定義應用程式的進入點。
//

#include "stdafx.h"
#include "OpenGLLab.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	GLFWwindow* window;

	/* Initialize the GLFW */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	// init glew must after glfwMakeContextCurrent()
	if (GLEW_OK != glewInit())
	{
		return -1;
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */

		// set background color MidnightBlue
		glClearColor(0.098039225f, 0.098039225f, 0.439215720f, 1.000000000f);
		glClear(GL_COLOR_BUFFER_BIT);

		// create vertexShader
		const char* vertexShaderSource =
			R"(#version 330

in vec4 position;

void main()
{
	gl_Position = position;
})";
		GLuint vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// create fragmentShader
		const char* fragmentShaderSource =
			R"(#version 330

out vec4 color;

void main()
{
    color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
})";

		GLuint fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		// create program
		GLuint shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);

		// prepare vertices data
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f,
		};

		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao); // Bind Vertex Array Object

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy our vertices array in a buffer for OpenGL to use
		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(posAttrib);

		glBindVertexArray(NULL); // Unbind the VAO

		glBindBuffer(GL_ARRAY_BUFFER, NULL); // Unbind the VBO

		//draw
		glBindVertexArray(vao); // Bind Vertex Array Object
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glBindVertexArray(0); // Unbind the VAO

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
