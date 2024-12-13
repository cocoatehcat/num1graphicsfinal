#include "skydome.h"
#include <iostream>

Skydome::Skydome(int numRows, int numCols, float rad, glm::vec3 camPos) {
	rows = numRows;
	columns = numCols;
	radius = rad;

    glGenVertexArrays(1, &skyVAO);
    glBindVertexArray(skyVAO);

    glGenBuffers(1, &skyVBO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);

    glGenBuffers(1, &skyEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    //normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);

    if(vertices.size() > 0){
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    }
    if(indices.size() > 0){
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
    }

    //numvertices = vertices.size
    //numindices = indices.size

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skydome::Render() {
	float subdivisions = columns - 1; //for test purposes - plane

	glm::vec3 v = glm::vec3(0);//vertex
    Vertex vv = Vertex();
	for (int r = 0; r <= subdivisions; r++) {
		for (int c = 0; c <= subdivisions; c++) {
			v.x = rows * (c/subdivisions);
			v.y = -float(columns) * (r / subdivisions);
            vv.position = v;
            vv.color = glm::vec4(1.0);
            vv.normal = glm::vec3(1.0);
			vertices.push_back(vv);
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

    int numIndices = indices.size();

    glBindVertexArray(skyVAO);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);


	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
//
//
//
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices, GL_STATIC_DRAW);
//
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices);
}