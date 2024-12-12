#pragma once

#include "../external/array_2d.h"


namespace terrain {
	class terrainClass {
	public:
		void loadHeightMap(const char* fileName);
		char* readFile(const char* fileName, int& size);

	protected:
		Array2D<float> heightMap; //Floating points allow for smoother terrain
		int terrainSize = 0;
	};
}