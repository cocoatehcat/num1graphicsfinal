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

//created files
#include <abrahmFiles/aShader.cpp>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	//X		Y		Z		NX		NY		NZ
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

const char* skyboxVertexSource = "assets/skydomeVert.vert";

const char* skyboxFragmentSource = "assets/skydomeFrag.frag";

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

	AShader skyboxShader(skyboxVertexSource, skyboxFragmentSource);

	// Enabled Depth for 3D objects
	glEnable(GL_DEPTH_TEST);

	// Inset mouse controls here once camera is implemented

	// VAO creation for terrain
	unsigned int TerrVAO;
	// vvv draw test
	glGenVertexArrays(1, &TerrVAO);
	glBindVertexArray(TerrVAO);

	// VBO creation
	unsigned int VBO;
	// vvv To test drawing to screen will work
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	

	// Implement the stride thingies
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

		skyboxShader.use();

		// uniforms
		int lightCol = glGetUniformLocation(shaderProgram, "lightColor");
		glUniform3f(lightCol, 1.0f, 1.0f, 1.0f); // change these to be functions in the shader class

		glm::mat4 model = glm::mat4(1.0f);

		glBindVertexArray(TerrVAO);

		//need shader files, but draws
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//actual output draw
		glfwSwapBuffers(window);

	}
	printf("Shutting down!. . .");
}