#pragma once

#include "../external/glad.h"
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace arout {
    class AShader {
        //program ID
        unsigned int id;

    public:
        // constructor
        AShader(const char *vertexPath, const char *fragmentPath);

        //use/activate shader
        void use();

        //utility uniform functions
        void setBool(const std::string &name, bool value) const;

        void setInt(const std::string &name, int value) const;

        void setFloat(const std::string &name, float value) const;

        void setVec3(const std::string &name, const glm::vec3 &value) const;

        void setMat4(const std::string &name, const glm::mat4 &m) const;
    };
}