#include "skydome.h"
#include "../external/ewMath.h"
#include <iostream>

namespace arout { //abrahm's skydome implementation
    //instantiates the skydome itself
    Skydome::Skydome(int numSegments, float rad) {
        radius = rad;
        segments = numSegments;

        auto v = glm::vec3(0.0f);
        auto vert = Vertex();

        glm::vec3 apexPoint(0.0f, radius, 0.0f);

        float thetaStep = 2 * ew::PI / float(numSegments);
        float phiStep = ew::PI / float(numSegments);

        //vertices
        vertices.clear();

        //top cap
        for(int i = 0; i <= numSegments; i++){
            float theta = i * thetaStep;
            v.x = cos(theta) * rad;
            v.z = sin(theta) * rad;
            v.y = 0;
            vertices.push_back(Vertex(v, glm::vec4(1.0, 0.5, 0.25, 1.0), glm::normalize(v)));
        }

        //body
        for (int row = 0; row <= (numSegments + 1) / 2; row++) {
            float phi = row * phiStep;
            for (int col = 0; col <= numSegments + 1; col++) {
                float theta = col * thetaStep;
                v.x = rad * cos(theta) * sin(phi);
                v.y = rad * cos(phi);
                v.z = rad * sin(theta) * sin(phi);
                vert.position = v;
                vert.color = glm::vec4(1.0, 0.5, 0.25, 1.0);
                vert.normal = glm::normalize(v);
                vertices.push_back(vert);
            }
        }

        //indices
        indices.clear();
        int domeColumns = numSegments + 1;
        for (int row = 0; row < (numSegments - 1) / 2; row++) {
            for (int col = 0; col < numSegments + 1; col++) {
                int start = row * domeColumns + col;
                //top right triangle
                indices.push_back(start);
                indices.push_back(start + 1);
                indices.push_back(start + domeColumns);
                //bottom left triangle
                indices.push_back(start + domeColumns + 1);
                indices.push_back(start + domeColumns);
                indices.push_back(start + 1);
            }
        }

        glGenVertexArrays(1, &skyVAO);
        glBindVertexArray(skyVAO);

        glGenBuffers(1, &skyVBO);
        glBindBuffer(GL_ARRAY_BUFFER, skyVBO);

        glGenBuffers(1, &skyEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);

        //position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        //color
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, color));
        glEnableVertexAttribArray(1);
        //normal
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);

        glBindVertexArray(skyVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        numVertices = vertices.size();
        numIndices = indices.size();

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Skydome::Render() {
        glBindVertexArray(skyVAO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

        //index draw
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
        //vertex draw
        glDrawArrays(GL_POINTS, 0, numVertices);
    }

    void Skydome::setRadius(float rad) { radius = rad; }
    void Skydome::setSegments(int segs) { segments = segs; }
}