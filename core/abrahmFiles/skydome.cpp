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
			vertices.push_back(v);
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

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());


}