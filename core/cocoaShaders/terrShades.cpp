#include "terrShades.h"

namespace teSh {
	// Use program
	void terrShades::use() {
		glUseProgram(ID);
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

	/*std::string vertexShaderSo;
std::string fragmentShaderSo;
std::tie(vertexShaderSo, fragmentShaderSo) = shad.readFile("assets/vertexShader.vert", "assets/fragmentShader.frag");

	const char* vertexShaderSource = vertexShaderSo.c_str();
	const char* fragmentShaderSource = fragmentShaderSo.c_str();

	// Check if Shader Compiles
	int  success = 0;
	char infoLog[512];

	// Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	shad.assignShader(vertexShader, 1, vertexShaderSource, success, infoLog);

	// Fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shad.assignShader(fragmentShader, 1, fragmentShaderSource, success, infoLog);

	// Creating a program
	unsigned int shaderProgram = glCreateProgram();
	shad.createProgram(shaderProgram, vertexShader, fragmentShader, success, infoLog); */
	/*
	* // VAO creation for terrain
	unsigned int TerrVAO;
	// vvv draw test
	glGenVertexArrays(1, &TerrVAO);
	glBindVertexArray(TerrVAO);

	// VBO creation
	unsigned int VBO;
	// vvv To test drawing to screen will work
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// XYZ
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// RGBA
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(sizeof(float)*3));
	//glEnableVertexAttribArray(1);

	// Normal XYZ
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(sizeof(float)*7));
	//glEnableVertexAttribArray(2);

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
	 *
	 */
	// TO ADD
	// those funkky little uniform expressions to be more automated
	// looks back at the file and see what was used a lot
}