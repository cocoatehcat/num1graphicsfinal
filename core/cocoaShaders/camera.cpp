// Created by Arija

#include "camera.h"

namespace cam {
	void Camera::processInput(GLFWwindow* window, float dt) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		float cameraSpeed = 10.0f * dt; // can be adjusted
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			cameraSpeed *= 2;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPos += cameraSpeed * cameraFront;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPos -= cameraSpeed * cameraFront;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			cameraPos += cameraUp * cameraSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			cameraPos -= cameraUp * cameraSpeed;
		}
	}

	// Function to create a random vec3
	glm::vec3 Camera::createPos() {
		float x, y, z;
		x = ew::RandomRange(-10.0f, 10.0f);
		y = ew::RandomRange(-10.0f, 10.0f);
		z = ew::RandomRange(-10.0f, 10.0f);
		return glm::vec3(x, y, z);
	}

	// Function to show mouse positioning
	void Camera::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // y coords go bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// Clamping
		if (pitch > 89.0f) {
			pitch = 89.0f;
		}
		if (pitch < -89.0f) {
			pitch = -89.0f;
		}

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);
		cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront)); // look into more
	}

	// Making it zoom
	void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		fov -= (float)yoffset;
		// Clamping
		if (fov < 1.0f) {
			fov = 1.0f;
		}
		if (fov > 120.0f) {
			fov = 120.0f;
		}
	}
}