#include "skydome.h"

Skydome::Skydome(int numRows, int numCols, float rad, glm::vec3 camPos) {
	rows = numRows;
	columns = numCols;
	radius = rad;
}

void Skydome::Render(unsigned int vao) {
	int subdivisions = columns - 1; //for test purposes - plane

	glm::vec3 v = glm::vec3(0);//vertex
	for (int r = 0; r <= subdivisions; r++) {
		for (int c = 0; c <= subdivisions; c++) {
			v.x = rows * (c/subdivisions);
			v.y = -columns * (r / subdivisions);
			vertices.push_back(v.x);
			vertices.push_back(v.y);
			vertices.push_back(v.z);
			//color
			vertices.push_back(0.0);
			vertices.push_back(1.0);
			vertices.push_back(1.0);
			vertices.push_back(1.0);
			//norm
			vertices.push_back(1.0);
			vertices.push_back(1.0);
			vertices.push_back(1.0);
		}
	}

	glm::vec3 i = glm::vec3(0);//index
	for (int r = 0; r <= subdivisions; r++) {
		for (int c = 0; c <= subdivisions; c++) {
			int start = r * columns * c;
			indices.push_back(start);
			indices.push_back(start + 1);
			indices.push_back(start + columns + 1);
		}
	}

	unsigned int SkyVBO;
	glGenBuffers(1, &SkyVBO);
	glBindBuffer(GL_ARRAY_BUFFER, SkyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	unsigned int SkyEBO;
	glGenBuffers(1, &SkyEBO);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());


}