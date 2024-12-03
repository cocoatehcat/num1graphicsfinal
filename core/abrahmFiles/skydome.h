#include <glm/glm.hpp>
#include "../external/glad.h"

//abrahm's skydome class :)
class Skydome {
	int rows;
	int columns;
	float radius;
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