#pragma once

#include "../external/glad.h"
#include <glm/fwd.hpp>
#include <fstream>
#include <sstream>
#include <tuple>
#include <math.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace teSh {
	class terrShades {
	public:
		terrShades(const char* vertexPath, const char* fragmentPath);
		void use();
		void setVec3(const std::string &name, const glm::vec3 &value) const;
		void setVec3(const std::string &name, float x, float y, float z) const;
		void setMat4(const std::string &name, const glm::mat4 &mat) const;
		void createVAO(int num, unsigned int* va);
		void createVBO(int num, unsigned int* vb);
		void createStride(int index, GLint in2, int length, int voidNum);
		std::tuple<std::string, std::string> readFile(const char* vertexPath, const char* fragmentPath);
		void assignShader(unsigned int ver, int i, const char* source, int wee, char log[]);
		void checkShadFail(unsigned int shader, int wee, char log[]);
		void createProgram(unsigned int vert, unsigned int frag, int wee, char log[]);
		void checkProCompile(int wee, char log[]);
		void genShader();

	private:
		unsigned int TerrVAO, VBO, ID;
	};
}