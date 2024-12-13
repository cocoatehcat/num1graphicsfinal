#include <stdio.h>
#include <vector>
#include <cmath>
#include <assert.h>

#include "triList.h"
#include "terrain.h"

void triList::createTriList(int widthIn, int depthIn, const terrainClass* terrain) {
	width = widthIn;
	depth = dpethIn;

	createGLState();

	populateBuffers(terrain);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void triList::createGLState() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);

	int POS_LOC = 0;

	glEnableVertexAttribArray(POS_LOC);

	size_t NumFloats = 0;
	glVertexAttribPointer(POS_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(NumFloats * sizeof(float)));
	NumFloats += 3;
}

void triList::populateBuffers(const terrainClass* terrain) {
	std::vector<Vertex> Vertices;
	Vertices.resize(width * depth);

	initVertices(terrain, Vertices);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
}

void triList::Vertex::initVertices(const terrainClass* terrain, int x, int z) {
	pos = Vector3f(x, 0.0f, z);

}

void triList::initVertices(const terrainClass* terrain, std::vector<Vertex>& Vertices) {
	int index = 0;

	for (int z = 0; z < depth; z++) {
		for (int x = 0; x < width; x++) {
			assert(index < Vertices.size());
			Vertices[index].initVertex(terrain, x, z);
			index++;
		}
	}
}

void triList::Render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, depth, width);
	glBindVertexArray(0);
}