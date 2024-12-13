#pragma once

#include "../external/outside/array_2d.h"
#include "triList.h"
#include "terrShades.h"


class terrainClass {
public:
	void loadHeightMap(const char* fileName);
	char* readFile(const char* fileName, int& size);
	void initTerrain();
	void Render();

protected:
	void loadHeightMapFile(const char* fileName);
	Array2D<float> heightMap; //Floating points allow for smoother terrain
	int terrainSize = 0;

	triList triListOb;
	teSh::terrShades terrSh;
};
