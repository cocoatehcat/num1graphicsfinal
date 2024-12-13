// Created by Arija!

#include "terrain.h"

Noise no = Noise();
cam::Camera came = cam::Camera();


// Renders the new terrain everyframe
// Only renders in a distance close to camera to reduce lag
void terrainClass::render(std::vector<GLuint>& map_chunks, teSh::terrShades& shader, glm::mat4& view, glm::mat4& model, glm::mat4& projection, int& nIndices) {
    glClearColor(0.53, 0.81, 0.92, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Measures number of map chunks away from origin map chunk the camera is
    gridPosX = (int)(came.cameraPos.x - originX) / chunkWidth + xMapChunks / 2;
    gridPosY = (int)(came.cameraPos.z - originY) / chunkHeight + yMapChunks / 2;

    // Render map chunks
    for (int y = 0; y < yMapChunks; y++)
        for (int x = 0; x < xMapChunks; x++) {
            // Only render chunk if it's within render distance
            if (std::abs(gridPosX - x) <= chunkRenderDistance && (y - gridPosY) <= chunkRenderDistance) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(-chunkWidth / 2.0 + (chunkWidth - 1) * x, 0.0, -chunkHeight / 2.0 + (chunkHeight - 1) * y));
                shader.setMat4("u_model", model);

                // Terrain chunk
                glBindVertexArray(map_chunks[x + y * xMapChunks]);
                glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);

            }
        }
}

// Generates a chunk
// Performs the OpenGL for it
void terrainClass::generateMapChunk(GLuint& VAO, int xOffset, int yOffset) {
    std::vector<int> indices;
    std::vector<float> noise_map;
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> colors;

    // Generate map
    indices = generateIndices();
    noise_map = generateNoiseMap(xOffset, yOffset);
    vertices = generateVertices(noise_map);
    normals = generateNormals(indices, vertices);
    colors = generateBiome(vertices, xOffset, yOffset);

    GLuint VBO[3], EBO;

    // Create buffers and arrays
    glGenBuffers(3, VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    // Bind vertices to VBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // Create element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    // Configure vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);

    // Configure vertex normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Bind vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STATIC_DRAW);

    // Configure vertex colors attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
}

// Gets color for the terrain
glm::vec3 terrainClass::getColor(int r, int g, int b) {
    return glm::vec3(r / 255.0, g / 255.0, b / 255.0);
}

// Makes the noise map the terrain is based off
std::vector<float> terrainClass::generateNoiseMap(int offsetX, int offsetY) {
    std::vector<float> noiseValues;
    std::vector<float> normalizedNoiseValues;
    std::vector<int> p = no.get_permutation_vector();

    float amp = 1;
    float freq = 1;
    float maxPossibleHeight = 0;

    for (int i = 0; i < octaves; i++) {
        maxPossibleHeight += amp;
        amp *= persistence;
    }

    for (int y = 0; y < chunkHeight; y++) {
        for (int x = 0; x < chunkWidth; x++) {
            amp = 1;
            freq = 1;
            float noiseHeight = 0;
            for (int i = 0; i < octaves; i++) {
                float xSample = (x + offsetX * (chunkWidth - 1)) / noiseScale * freq;
                float ySample = (y + offsetY * (chunkHeight - 1)) / noiseScale * freq;

                float perlinValue = no.perlin_noise(xSample, ySample, p);
                noiseHeight += perlinValue * amp;

                // Lacunarity  --> Increase in frequency of octaves
                // Persistence --> Decrease in amplitude of octaves
                amp *= persistence;
                freq *= lacunarity;
            }

            noiseValues.push_back(noiseHeight);
        }
    }

    for (int y = 0; y < chunkHeight; y++) {
        for (int x = 0; x < chunkWidth; x++) {
            // Inverse lerp and scale values to range from 0 to 1
            normalizedNoiseValues.push_back((noiseValues[x + y * chunkWidth] + 1) / maxPossibleHeight);
        }
    }

    return normalizedNoiseValues;
}

// Makes different colors for the chunks
std::vector<float> terrainClass::generateBiome(const std::vector<float>& vertices, int xOffset, int yOffset) {
    std::vector<float> colors;
    std::vector<terrainColor> biomeColors;
    glm::vec3 color = getColor(255, 255, 255);

    // NOTE: Terrain color height is a value between 0 and 1
    biomeColors.push_back(terrainColor(WATER_HEIGHT * 0.5, getColor(60, 95, 190)));     // Deep water
    biomeColors.push_back(terrainColor(WATER_HEIGHT, getColor(60, 100, 190)));          // Shallow water
    biomeColors.push_back(terrainColor(0.15, getColor(210, 215, 130)));           // Sand
    biomeColors.push_back(terrainColor(0.30, getColor(95, 165, 30)));             // Grass 1
    biomeColors.push_back(terrainColor(0.40, getColor(65, 115, 20)));             // Grass 2
    biomeColors.push_back(terrainColor(0.50, getColor(90, 65, 60)));              // Rock 1
    biomeColors.push_back(terrainColor(0.80, getColor(75, 60, 55)));              // Rock 2
    biomeColors.push_back(terrainColor(1.00, getColor(255, 255, 255)));           // Snow


    // Determine which color to assign each vertex by its y-coord
    // Iterate through vertex y values
    for (int i = 1; i < vertices.size(); i += 3) {
        for (int j = 0; j < biomeColors.size(); j++) {
            // NOTE: The max height of a vertex is "meshHeight"
            if (vertices[i] <= biomeColors[j].height * meshHeight) {
                color = biomeColors[j].color;
                break;
            }
        }
        colors.push_back(color.r);
        colors.push_back(color.g);
        colors.push_back(color.b);
    }
    return colors;
}

// Gets the normals for the lighting
std::vector<float> terrainClass::generateNormals(const std::vector<int>& indices, const std::vector<float>& vertices) {
    int pos;
    glm::vec3 normal;
    std::vector<float> normals;
    std::vector<glm::vec3> verts;

    // Get the vertices of each triangle in mesh
    // For each group of indices
    for (int i = 0; i < indices.size(); i += 3) {

        // Get the vertices (point) for each index
        for (int j = 0; j < 3; j++) {
            pos = indices[i + j] * 3;
            verts.push_back(glm::vec3(vertices[pos], vertices[pos + 1], vertices[pos + 2]));
        }

        // Get vectors of two edges of triangle
        glm::vec3 U = verts[i + 1] - verts[i];
        glm::vec3 V = verts[i + 2] - verts[i];

        // Calculate normal
        normal = glm::normalize(-glm::cross(U, V));
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
    }

    return normals;
}

// Creates the vertices to be used for the mesh
std::vector<float> terrainClass::generateVertices(const std::vector<float>& noise_map) {
    std::vector<float> v;

    for (int y = 0; y < chunkHeight + 1; y++)
        for (int x = 0; x < chunkWidth; x++) {
            v.push_back(x);
            // Apply cubic easing to the noise
            float easedNoise = std::pow(noise_map[x + y * chunkWidth] * 1.1, 3);
            // Scale noise to match meshHeight
            // Pervent vertex height from being below WATER_HEIGHT
            v.push_back(std::fmax(easedNoise * meshHeight, WATER_HEIGHT * 0.5 * meshHeight));
            v.push_back(y);
        }

    return v;
}

// Makes Indices to be more efficient
std::vector<int> terrainClass::generateIndices() {
    std::vector<int> indices;

    for (int y = 0; y < chunkHeight; y++)
        for (int x = 0; x < chunkWidth; x++) {
            int pos = x + y * chunkWidth;

            if (x == chunkWidth - 1 || y == chunkHeight - 1) {
                // Don't create indices for right or top edge
                continue;
            }
            else {
                // Top left triangle of square
                indices.push_back(pos + chunkWidth);
                indices.push_back(pos);
                indices.push_back(pos + chunkWidth + 1);
                // Bottom right triangle of square
                indices.push_back(pos + 1);
                indices.push_back(pos + 1 + chunkWidth);
                indices.push_back(pos);
            }
        }

    return indices;
}