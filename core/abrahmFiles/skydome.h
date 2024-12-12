#pragma once

#include <glm/glm.hpp>
#include "../external/glad.h"
#include <vector>

//abrahm's skydome class :)
class Skydome {
	int rows;
	int columns;
	float radius;
	std::vector<glm::vec3> vertices;
	std::vector<int> indices;
	
public:
	//constructor
	Skydome(int numRows, int numCols, float rad, glm::vec3 camPos);

	//use function
	void Render();

	//wireframe
	void SetVisibility(bool wireTrue);

	//setters
	void setRows(int numRows);
	void setCols(int numCols);
	void setRadius(float rad);
};