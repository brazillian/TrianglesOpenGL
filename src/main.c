/*
 * main.c
 *
 *  Created on: 4 de jan. de 2022
 *      Author: Familia PC - NETWORK
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define WIDTH 800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_pressed(GLFWwindow * window);
void compile_log(unsigned int shader_id, char * shader_type);

const char *vertex_shader_source = "#version 330 core\n"
	    "layout (location = 0) in vec3 aPos;\n"
	    "void main()\n"
	    "{\n"
	    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	    "}\0";

const char *fragmentShaderSource1 = "#version 330 core\n"
	    "out vec4 FragColor;\n"
	    "void main()\n"
	    "{\n"
	    "   FragColor = vec4(0.78f, 0.20f, 0.55f, 1.0f);\n"
	    "}\n\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
	    "out vec4 FragColor;\n"
	    "void main()\n"
	    "{\n"
	    "   FragColor = vec4(0.3f, 0.6f, 0.89f, 1.0f);\n"
	    "}\n\0";




int main (void) {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);

	if (window == NULL) {
		printf("A error at creating the object window ocurred!!!\n");
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
	    printf("Failed to initialize GLAD!!!\n");
	    return -1;
	}

	// Create a vertex shader and two fragment shaders
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertexShader);

	compile_log(vertexShader, "vertex_Shader");

	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentShader1);
	compile_log(fragmentShader1, "fragment_Shader");

	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	compile_log(fragmentShader2, "fragment_Shader");


	// Create the shaders programs
	unsigned int shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	compile_log(shaderProgram1, "shader_program");

	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	compile_log(shaderProgram2, "shader_program");


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);

	float firstTriangle[] = {
			0.0f,  -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.25f, 0.0f, 0.0f,


			0.0f, 0.0f, 0.0f,
			-0.5f, 0.0f, 0.0f,
			-0.25f, 0.5f, 0.0f
	};

	float secondTriangle[] = {
				0.0f,  0.0f, 0.0f,
				0.25f, 0.5f, 0.0f,
				0.5f, 0.0f, 0.0f,

				0.5f, 0.0f, 0.0f,
				0.0f,  0.0f, 0.0f,
				0.25f, -0.5f,0.0f


		};

	// CREATE THE VAO's and VBO's
	unsigned int VAO[2], VBO[2] ;
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	// SET THE FIRST VAO and VBO
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// SET THE SCOND VAO and VBO
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {

		key_pressed(window);

		glClearColor(0.8f, 0.5f,0.4f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES,0, 6);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width , height);
}

void key_pressed(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void compile_log(unsigned int shader_id, char * shader_type) {
	int success;
	char info_log[512];

	if (strcmp(shader_type, "shader_program") == 0) {
		glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader_id, 512, NULL, info_log);
			printf("An error occurred in the linking of the shader program\n");
		}
	}
	else {
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader_id, 512, NULL, info_log);
			printf("An error occurred in the compiling of the %s\n", shader_type);
		}
	}

}

