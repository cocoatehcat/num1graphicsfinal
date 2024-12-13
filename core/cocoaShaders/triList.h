#pragma once

#include <vector>
#include <cmath>
#include <stdio.h>
#include "../external/glad.h"

class terrainClass;

class triList {
public:
	triList();

	void createTriList(int widthIn, int depthIn, const terrainClass* terrain);

	void Render();

private:
	int width = 0;
	int depth = 0;
	GLuint vao;
	GLuint vb;
	GLuint ib;

	struct Vertex {
		std::vector<float> pos;

		void initVertex(const terrainClass* terrain, int x, int z);
	};

	void createGLState();
	void populateBuffers(const terrainClass* terrain);
	void initVertices(const terrainClass* terrain, std::vector<Vertex>& Vertices);
};