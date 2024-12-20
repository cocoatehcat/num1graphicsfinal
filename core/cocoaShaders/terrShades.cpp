// Created by Arija

#include "terrShades.h"

namespace teSh {
	// Use program
	void terrShades::use() {
		glUseProgram(ID);
	}

	//Uniforms
	void terrShades::setVec3(const std::string &name, const glm::vec3 &value) const {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void terrShades::setVec3(const std::string &name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	// View matrix
	void terrShades::setMat4(const std::string &name, const glm::mat4 &mat) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	// Took from Abrahm
	terrShades::terrShades(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {

		//open the files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		//read file buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//close files
		vShaderFile.close();
		fShaderFile.close();

		//convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
	}

	//fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", infoLog);
	}

	//shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	//print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", infoLog);
	}
	//delete shaders - linked in
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

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
		glVertexAttribPointer(index, in2, GL_FLOAT, GL_FALSE, length * sizeof(float), (void*)(sizeof(float) * voidNum));
		glEnableVertexAttribArray(index);
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
	void terrShades::createProgram(unsigned int vert, unsigned int frag, int wee, char log[]) {
		glAttachShader(ID, vert);
		glAttachShader(ID, frag);
		glLinkProgram(ID);
		glUseProgram(ID);

		checkProCompile(wee, log);
	}

	// checks to see if shader program compiles
	void terrShades::checkProCompile(int wee, char log[]) {
		glGetProgramiv(ID, GL_LINK_STATUS, &wee);

		if (!wee) {
			glGetProgramInfoLog(ID, 512, NULL, log);
			printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", log);
		}
	}

	void terrShades::genShader() {
		std::string vertexShaderSo;
		std::string fragmentShaderSo;
		std::tie(vertexShaderSo, fragmentShaderSo) = readFile("assets/terrain.vert", "assets/terrain.frag");

		const char* vertexShaderSource = vertexShaderSo.c_str();
		const char* fragmentShaderSource = fragmentShaderSo.c_str();

		// Check if Shader Compiles
		int  success = 0;
		char infoLog[512];

		// Vertex Shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		assignShader(vertexShader, 1, vertexShaderSource, success, infoLog);

		// Fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		assignShader(fragmentShader, 1, fragmentShaderSource, success, infoLog);

		// Creating a program
		ID = glCreateProgram();
		createProgram(vertexShader, fragmentShader, success, infoLog);
	}
}
