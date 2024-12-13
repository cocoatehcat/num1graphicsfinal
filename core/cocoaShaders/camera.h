#pragma once

#include "../external/glad.h"
#include "../external/ewMath.h"
#include <math.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cam {
	class Camera {
	public:
		void processInput(GLFWwindow* window, float dt);
		glm::vec3 createPos();
		void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

		glm::vec3 getPos() { return cameraPos; }
		glm::vec3 getFront() { return cameraFront; }
		glm::vec3 getUp() { return cameraUp; }
		float getFOV() { return fov; }
		glm::vec3 cameraPos = glm::vec3(0.0f, 10.0f, 3.0f);

	private:

		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

		bool firstMouse = true;
		float yaw = -90.0f;
		float pitch = 0.0f;
		float lastX = 1080.0f / 2.0;
		float lastY = 720.0f / 2.0;
		float fov = 60.0f;
	};
}