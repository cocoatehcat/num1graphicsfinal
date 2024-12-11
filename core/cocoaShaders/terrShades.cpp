#include "terrShades.h"

namespace teSh {
	// Create VAO
	void terrShades::createVAO(int num, unsigned int* va) {
		glGenVertexArrays(num, va);
		glBindVertexArray(*va);
	}

	// Create VBO, add that one line in main
	void terrShades::createVBO(int num, unsigned int* vb) {
		glGenBuffers(num, vb);
		glBindBuffer(GL_ARRAY_BUFFER, *vb);
	}

	// Set stride for VAO and VBO
	void terrShades::createStride(int index, GLint in2, int length, int voidNum) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, in2, GL_FLOAT, GL_FALSE, length * sizeof(float), (void*)(sizeof(float) * voidNum));
	}

	// This will be to upload files, specifically the vertex and fragment shaders
	std::tuple<std::string, std::string> terrShades::readFile(const char* vertexPath, const char* fragmentPath) {
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// 2. ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath); 
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) // if it fails, cry.
		{
			printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
		}

		return { vertexCode, fragmentCode };
	}

	//this puts the file  in the right shader
	void terrShades::assignShader(unsigned int ver, int i, const char* source, int wee, char log[]) {
		glShaderSource(ver, i, &source, NULL);
		glCompileShader(ver);

		checkShadFail(ver, wee, log);
	}

	//this checks if the shader fails
	void terrShades::checkShadFail(unsigned int shader, int wee, char log[]) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &wee);

		if (!wee) {
			glGetShaderInfoLog(shader, 512, NULL, log);
			printf("ERROR::SHADER::COMPILATION_FAILED\n%s", log);
		}
	}

	// creates shader program
	void terrShades::createProgram(unsigned int prog, unsigned int vert, unsigned int frag, int wee, char log[]) {
		glAttachShader(prog, vert);
		glAttachShader(prog, frag);
		glLinkProgram(prog);
		glUseProgram(prog);

		checkProCompile(prog, wee, log);
	}

	// checks to see if shader program compiles
	void terrShades::checkProCompile(unsigned int prog, int wee, char log[]) {
		glGetProgramiv(prog, GL_LINK_STATUS, &wee);

		if (!wee) {
			glGetProgramInfoLog(prog, 512, NULL, log);
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", log);
		}
	}

	// TO ADD
	// those funkky little uniform expressions to be more automated
	// looks back at the file and see what was used a lot
}