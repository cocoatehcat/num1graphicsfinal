#include "skydome.h"
#include "../external/ewMath.h"
#include <iostream>

Skydome::Skydome(int numSegments, float rad, glm::vec3 camPos) {
	//rows = numRows;
	//columns = numCols;
	radius = rad;
    //verticesTop = 3 * numCols;
    verticesRegular = numSegments;
    //numVertices = verticesTop + (numRows - 1) * verticesRegular;
//
    //float pitchAngle = 90.0f / float(numRows);
    //float headingAngle = 360.0f / float(numCols);

    auto v = glm::vec3(0.0f);
    auto vert = Vertex();

    glm::vec3 apexPoint(0.0f, radius, 0.0f);

    //float pitch = -90.0f;

    float thetaStep = 2 * ew::PI / numSegments;
    float phiStep = ew::PI / float(numSegments);

    vertices.clear();
    //vertice
    for(int row = 0; row <= numSegments/2; row++){
        float phi = row * phiStep;
        for(int col = 0; col <= numSegments; col++){
            float theta = col * thetaStep;
            v.x = rad * cos(theta) * sin(phi);
            v.y = rad * cos(phi);
            v.z = rad * sin(theta) * sin(phi);
            vert.position = v;
            vert.color = glm::vec4(1.0);
            vert.normal = glm::normalize(v);
            vertices.push_back(vert);
        }
    }
    indices.clear();
    //indices
    int fuckingColumns = numSegments + 1;
    for(int row = 1; row < numSegments - 1; row++){
        for(int col = 0; col < numSegments; col++){
            int start = row * fuckingColumns + col;
            //topR triangle
            indices.push_back(start);
            indices.push_back(start+1);
            indices.push_back(start+fuckingColumns);
            //botL trangle
            indices.push_back(start+fuckingColumns+1);
            indices.push_back(start+fuckingColumns);
            indices.push_back(start+1);
        }
    }


    //float subdivisions = columns - 1; //for test purposes - plane
//
    //glm::vec3 v = glm::vec3(0);//vertex
    //Vertex vv = Vertex();
    //for (int r = 0; r <= subdivisions; r++) {
    //    for (int c = 0; c <= subdivisions; c++) {
    //        v.x = rows * (c/subdivisions);
    //        v.y = -float(columns) * (r / subdivisions);
    //        vv.position = v;
    //        vv.color = glm::vec4(1.0);
    //        vv.normal = glm::vec3(1.0);
    //        vertices.push_back(vv);
    //    }
    //}
//
    //glm::vec3 i = glm::vec3(0);//index
    //for (int r = 0; r <= subdivisions; r++) {
    //    for (int c = 0; c <= subdivisions; c++) {
    //        int start = r * columns * c;
    //        indices.push_back(start);
    //        indices.push_back(start + 1);
    //        indices.push_back(start + columns + 1);
    //    }
    //}

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

    numVertices = vertices.size();
    numIndices = indices.size();

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skydome::Render() {
	//float subdivisions = columns - 1; //for test purposes - plane
//
	//glm::vec3 v = glm::vec3(0);//vertex
    //Vertex vv = Vertex();
	//for (int r = 0; r <= subdivisions; r++) {
	//	for (int c = 0; c <= subdivisions; c++) {
	//		v.x = rows * (c/subdivisions);
	//		v.y = -float(columns) * (r / subdivisions);
    //        vv.position = v;
    //        vv.color = glm::vec4(1.0);
    //        vv.normal = glm::vec3(1.0);
	//		vertices.push_back(vv);
	//	}
	//}
//
	//glm::vec3 i = glm::vec3(0);//index
	//for (int r = 0; r <= subdivisions; r++) {
	//	for (int c = 0; c <= subdivisions; c++) {
	//		int start = r * columns * c;
	//		indices.push_back(start);
	//		indices.push_back(start + 1);
	//		indices.push_back(start + columns + 1);
	//	}
	//}
    int numSegments = verticesRegular;
    float rad = radius;
    auto v = glm::vec3(0.0f);
    auto vert = Vertex();

    glm::vec3 apexPoint(0.0f, radius, 0.0f);

    float thetaStep = 2 * ew::PI / numSegments;
    float phiStep = ew::PI / numSegments;

    //vertices.clear();
    //vertices
    for(int row = 0; row <= numSegments; row++){
        float phi = row * phiStep;
        for(int col = 0; col <= numSegments; col++){
            float theta = col * thetaStep;
            v.x = rad * cos(theta) * sin(phi);
            v.z = rad * cos(phi);
            v.y = rad * sin(theta) * sin(phi);
            vert.position = v;
            vert.color = glm::vec4(1.0);
            vert.normal = glm::vec3(0.0);
            vertices.push_back(vert);
        }
    }

    //indices.clear();
    //indices
    int fuckingColumns = numSegments + 1;
    for(int row = 1; row < numSegments - 1; row++){
        for(int col = 0; col < numSegments; col++){
            int start = row * fuckingColumns + col;
            //topR triangle
            indices.push_back(start);
            indices.push_back(start+1);
            indices.push_back(start+fuckingColumns);
            //botL trangle
            indices.push_back(start+fuckingColumns+1);
            indices.push_back(start+fuckingColumns);
            indices.push_back(start+1);
        }
    }

    numVertices = vertices.size();
    numIndices = indices.size();

    glBindVertexArray(skyVAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
    glDrawArrays(GL_POINTS, 0 , numVertices);


	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
//
//
//
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices, GL_STATIC_DRAW);
//
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices);
}

void Skydome::setRows(int numRows) {rows = numRows;}
void Skydome::setCols(int numCols) {columns = numCols;}
void Skydome::setRadius(float rad) {radius = rad;}