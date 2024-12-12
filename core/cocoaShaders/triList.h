#pragma once

#include "../external/glew.h"
#include <vector>
#include <cmath>
#include <stdio.h>

#include "../external/ogldev_math_3d.h"

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
		Vector3f pos;

		void initVertex(const terrainClass* terrain, int x, int z);
	};

	void createGLState();
	void populateBuffers(const terrainClass* terrain);
	void initVertices(const terrainClass* terrain, std::vector<Vertex>& Vertices);
};