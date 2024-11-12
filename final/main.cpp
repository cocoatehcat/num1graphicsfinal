#include <stdio.h>
#include <math.h>
#include <fstream>

#include <external/glad.h>
#include <external/stb_image.h>
#include <external/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lighting", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}

	// Initialization! Wooooo

	// Enabled Depth for 3D objects
	glEnable(GL_DEPTH_TEST);

	// Inset mouse controls here once camera is implemented

	// VAO creation for terrain
	unsigned int TerrVAO;

	// VBO creation
	unsigned int VBO;

	// Implement the stride thingies

	// Read from files (use the read file function in shaders)

	// Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Fragment Shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Create a program
	unsigned int shaderProgram = glCreateProgram();

	// Once shaders are done with, delete
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Maybe include something about time?
	float prevTime = 0;

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Calculate delta time
		float time = (float)glfwGetTime();
		float deltaTime = time - prevTime;
		prevTime = time;

		// get input from camera

		// Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use shader program
		glUseProgram(shaderProgram);

		// uniforms
		int lightCol = glGetUniformLocation(shaderProgram, "lightColor");
		glUniform3f(lightCol, 1.0f, 1.0f, 1.0f); // change these to be functions in the shader class

		glm::mat4 model = glm::mat4(1.0f);

	}
	printf("Shutting down!. . .");
}