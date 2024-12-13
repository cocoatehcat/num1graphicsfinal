#pragma once

#include <glm/glm.hpp>
#include "../external/glad.h"
#include <vector>


//abrahm's skydome class :)
namespace arout {
    class Skydome {
    public:
        struct Vertex {
            glm::vec3 position = glm::vec3(0);
            glm::vec4 color = glm::vec4(0);
            glm::vec3 normal = glm::vec3(0);

            Vertex() = default;

            Vertex(const glm::vec3 &pos, const glm::vec4 &col, const glm::vec3 norm) {
                position = pos;
                color = col;
                normal = norm;
            }
        };

        //constructor
        Skydome(int numSegments, float rad);

        //use function
        void Render();

        //setters
        void setRadius(float rad);
        void setSegments(int segs);

    private:
        float radius;
        unsigned int skyVAO;
        unsigned int skyVBO;
        unsigned int skyEBO;
        int segments;
        int numVertices;
        std::vector<Vertex> vertices;
        int numIndices;
        std::vector<int> indices;
    };
}