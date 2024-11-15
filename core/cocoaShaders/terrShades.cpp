#include "terrShades.h"

namespace teSh {
	void terrShades::createVAO() {
		// insert stuff in here later
	}

	void terrShades::createVBO() {
		//rahhh
	}

	void terrShades::createStride() {
		// this one is to set the stride for the VBO and VAO
	}

	std::tuple<std::string, std::string> terrShades::readFile(const char* vertexPath, const char* fragmentPath) {
		// This will be to upload files, specifically the vertex and fragment shaders
	}

	void terrShades::assignShader() {
		//this puts the file and stuff in the right shader
	}

	void terrShades::checkShadFail() {
		//this checks if the shader fails
	}

	void terrShades::createProgram() {
		// creates shader program
	}

	void terrShades::checkProCompile() {
		// checks to see if shader program compiles
	}

	// TO ADD
	// those funkky little uniform expressions to be more automated
	// looks back at the file and see what was used a lot
}