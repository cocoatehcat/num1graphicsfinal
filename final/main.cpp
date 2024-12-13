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
#include <cocoaShaders/terrain.h>

#include <abrahmFiles/skydome.cpp>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

const char* skyboxVertexSource = "assets/skydomeVert.vert";

const char* skyboxFragmentSource = "assets/skydomeFrag.frag";

cam::Camera camera = cam::Camera();
terrainClass teCl = terrainClass();

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	camera.mouse_callback(window, xposIn, yposIn);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.scroll_callback(window, xoffset, yoffset);
}

// FPS
double lastTime = glfwGetTime();
int nbFrames = 0;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame;

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

	// Arija's terrain
	// Initalize variables
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 projection;


	const char* terrainVertex = "assets/terrain.vert";
	const char* terrainFragment = "assets/terrain.frag";

	teSh::terrShades terr(terrainVertex, terrainFragment);

	// Default to coloring to flat mode
	terr.use();

	// Lighting intensities and direction
	terr.setVec3("light.ambient", 0.2, 0.2, 0.2);
	terr.setVec3("light.diffuse", 0.3, 0.3, 0.3);
	terr.setVec3("light.specular", 1.0, 1.0, 1.0);
	terr.setVec3("light.direction", -0.2f, -1.0f, -0.3f);

	// Terrain class
	terrainClass terr1 = terrainClass();

	std::vector<GLuint> map_chunks(terr1.getxChunk() * terr1.getyChunk());

	for (int y = 0; y < terr1.getyChunk(); y++)
		for (int x = 0; x < terr1.getxChunk(); x++) {
			terr1.generate_map_chunk(map_chunks[x + y * terr1.getxChunk()], x, y);
		}

	int nIndices = terr1.getChunkWidth() * terr1.getChunkHeight() * 6;

	// Maybe include something about time?
	float prevTime = 0;

	// Cube position
	glm::vec3 cubePos(1.0f, 1.0f, 1.0f);	

	//skydome
	Skydome theDamnSky = Skydome(30, 65.0f, glm::vec3(0));

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

		// Draw the mesh
		terr.use();
		projection = glm::perspective(glm::radians(camera.getFOV()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, (float)terr1.getChunkWidth() * (terr1.getchunkRenDis() - 1.2f));
		float radius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), camera.getUp());
		terr.setMat4("u_projection", projection);
		terr.setMat4("u_view", view);
		terr.setVec3("u_viewPos", camera.cameraPos);

		terr1.render(map_chunks, terr, view, model, projection, nIndices);

		// Using the shader!
		skyboxShader.use();

		// Projection matrix
		glm::mat4 project = glm::perspective(glm::radians(camera.getFOV()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
		skyboxShader.setMat4("proj", project);

		//View
		glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // moving scene back to make it seems right to us
		radius = 10.0f;
		camX = static_cast<float>(sin(glfwGetTime()) * radius);
		camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), camera.getUp());
		skyboxShader.setMat4("view", view);

		// Model
		glm::mat4 model = glm::mat4(1.0f);
		skyboxShader.setMat4("model", model);


		//need shader files, but draws
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//glDisable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		theDamnSky.Skydome::Render();

		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Unlocks
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Locks


		//actual output draw
		glfwSwapBuffers(window);

	}
	printf("Shutting down!. . .");
}

/* // IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

const GLint WIDTH = 1920, HEIGHT = 1080;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

cam::Camera camera = cam::Camera();
terrainClass terr = terrainClass();

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    camera.mouse_callback(window, xposIn, yposIn);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.scroll_callback(window, xoffset, yoffset);
}

// FPS
double lastTime = glfwGetTime();
int nbFrames = 0;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame;

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

    //Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Enable z-buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    // Enable mouse input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initalize variables
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 projection;

    Shader objectShader("objectShader.vert", "objectShader.frag");

    // Default to coloring to flat mode
    objectShader.use();
    objectShader.setBool("isFlat", true);

    // Lighting intensities and direction
    objectShader.setVec3("light.ambient", 0.2, 0.2, 0.2);
    objectShader.setVec3("light.diffuse", 0.3, 0.3, 0.3);
    objectShader.setVec3("light.specular", 1.0, 1.0, 1.0);
    objectShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);

    std::vector<GLuint> map_chunks(terr.getxChunk() * terr.getyChunk());

    for (int y = 0; y < terr.getyChunk(); y++)
        for (int x = 0; x < terr.getxChunk(); x++) {
            terr.generate_map_chunk(map_chunks[x + y * terr.getxChunk()], x, y);
        }

    int nIndices = terr.getChunkWidth() * terr.getChunkHeight() * 6;

    while (!glfwWindowShouldClose(window)) {
        objectShader.use();
        projection = glm::perspective(glm::radians(camera.getFOV()), (float)WIDTH / (float)HEIGHT, 0.1f, (float)terr.getChunkWidth() * (terr.getchunkRenDis() - 1.2f));
        float radius = 10.0f;
        float camX = static_cast<float>(sin(glfwGetTime()) * radius);
        float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
        view = glm::lookAt(camera.getPos(), camera.getPos() + camera.getFront(), camera.getUp());
        objectShader.setMat4("u_projection", projection);
        objectShader.setMat4("u_view", view);
        objectShader.setVec3("u_viewPos", camera.cameraPos);

        terr.render(map_chunks, objectShader, view, model, projection, nIndices);
    }

    for (int i = 0; i < map_chunks.size(); i++) {
        glDeleteVertexArrays(1, &map_chunks[i]);
    }*/