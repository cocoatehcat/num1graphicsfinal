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
#include <cocoaShaders/terrShades.h>
#include <cocoaShaders/camera.h>
#include <abrahmFiles/skydome.cpp>
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

float vertices[] = {
	//X		Y		Z	R   G   B   A	NX		NY		NZ
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f,1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f,0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f,0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f,0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f,0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,0.0f,  1.0f,  0.0f
};

const char* skyboxVertexSource = "assets/skydomeVert.vert";

const char* skyboxFragmentSource = "assets/skydomeFrag.frag";

teSh::terrShades terr = teSh::terrShades();
cam::Camera camera = cam::Camera();

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	camera.mouse_callback(window, xposIn, yposIn);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.scroll_callback(window, xoffset, yoffset);
}

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Abrahm's & Arija's Amazing Final Project", NULL, NULL);
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

	// Inset mouse controls here once camera is implemented
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Enabled Depth for 3D objects + culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

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

	// XYZ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // RGBA
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    // Normal XYZ
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(sizeof(float)*7));
    glEnableVertexAttribArray(2);

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

	// Cube position
	glm::vec3 cubePos(1.0f, 1.0f, 1.0f);	

	//skydome
	Skydome theDamnSky = Skydome(5, 5, 1.0, glm::vec3(0));	
	 
	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Calculate delta time
		float time = (float)glfwGetTime();
		float deltaTime = time - prevTime;
		prevTime = time;

		// get input from camera
		// Getting input
		camera.processInput(window, deltaTime);

		// Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Using the shader!
		skyboxShader.use();

		// Projection matrix
		glm::mat4 project = glm::perspective(glm::radians(camera.getFOV()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		skyboxShader.setMat4("proj", project);

		//View
		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // moving scene back to make it seems right to us
		float radius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), camera.getUp());
		skyboxShader.setMat4("view", view);

		// Model
		glm::mat4 model = glm::mat4(1.0f);
		skyboxShader.setMat4("model", model);

		glBindVertexArray(TerrVAO);

		//need shader files, but draws
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT, GL_LINE);
		theDamnSky.Render(TerrVAO);

		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Unlocks
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Locks

		//actual output draw
		glfwSwapBuffers(window);

	}
	printf("Shutting down!. . .");
}