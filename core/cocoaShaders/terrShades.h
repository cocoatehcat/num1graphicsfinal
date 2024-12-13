#pragma once

#include "../external/glad.h"
#include <fstream>
#include <sstream>
#include <tuple>

namespace teSh {
	class terrShades {
	public:
		void use();
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