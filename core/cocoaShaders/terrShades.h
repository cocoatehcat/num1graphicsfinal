#pragma once

#include "../external/glad.h"
#include <fstream>
#include <sstream>
#include <tuple>

namespace teSh {
	class terrShades {
	public:
		void createVAO();
		void createVBO();
		void createStride();
		std::tuple<std::string, std::string> readFile(const char* vertexPath, const char* fragmentPath);
		void assignShader();
		void checkShadFail();
		void createProgram();
		void checkProCompile();
	};
}