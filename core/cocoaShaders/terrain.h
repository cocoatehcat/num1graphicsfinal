// Created by Arija
// Followed a tutorial:
// https://github.com/LiamHz/atlas
// Also referenced this series
// https://www.youtube.com/watch?v=xoqESu9iOUE&list=PLA0dXqQjCx0S9qG5dWLsheiCJV-_eLUM0&index=5

#pragma once

#include "terrShades.h"
#include <vector>
#include <string.h>
#include <cmath>
#include "camera.h"
#include "../external/glad.h"
#include <glm/fwd.hpp>
#include "noise.h"
#include "../external/ewMath.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class terrainClass {
public:
	void render(std::vector<GLuint>& map_chunks, teSh::terrShades& shader, glm::mat4& view, glm::mat4& model, glm::mat4& projection, int& nIndices);
	std::vector<int> generateIndices();
	std::vector<float> generateNoiseMap(int xOffset, int yOffset);
	std::vector<float> generateVertices(const std::vector<float>& noise_map);
	std::vector<float> generateNormals(const std::vector<int>& indices, const std::vector<float>& vertices);
	std::vector<float> generateBiome(const std::vector<float>& vertices, int xOffset, int yOffset);
	void generateMapChunk(GLuint& VAO, int xOffset, int yOffset);
	glm::vec3 getColor(int r, int g, int b);

	int getWater() { return WATER_HEIGHT; }
	int getchunkRenDis() { return chunkRenderDistance; }
	int getxChunk() { return xMapChunks; }
	int getyChunk() { return yMapChunks; }
	int getChunkWidth() { return chunkWidth; }
	int getChunkHeight() { return chunkHeight; }
	int getgridX() { return gridPosX; }
	int getgridY() { return gridPosY; }

private:
	// Map params
	float WATER_HEIGHT = 0.1;
	int chunkRenderDistance = 3;
	int xMapChunks = 10;
	int yMapChunks = 10;
	int chunkWidth = 127;
	int chunkHeight = 127;
	int gridPosX = 0;
	int gridPosY = 0;
	float originX = (chunkWidth * xMapChunks) / 2 - chunkWidth / 2;
	float originY = (chunkHeight * yMapChunks) / 2 - chunkHeight / 2;

	// Noise params
	int octaves = 5;
	float meshHeight = 32;  // Vertical scaling
	float noiseScale = 64;  // Horizontal scaling
	float persistence = 0.5;
	float lacunarity = 2;

	struct terrainColor {
		terrainColor(float _height, glm::vec3 _color) {
			height = _height;
			color = _color;
		};
		float height;
		glm::vec3 color;
	};
};
