#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <cerrno>
#include <sys/stat.h>
#include <cmath>

#include "terrain.h"

namespace terrain {
	// Loads a heightmap for the program
	void terrainClass::loadHeightMap(const char* fileName) {
		int fileSize = 0;
		unsigned char* p = (unsigned char*)readFile(fileName, fileSize);

		assert(fileSize % sizeof(float) == 0);

		terrainSize = sqrtf(fileSize / sizeof(float));

		// Uses terrainSize for height and width
		heightMap.InitArray2D(terrainSize, terrainSize, p);

		heightMap.PrintFloat();
	}

	// Reading simple file
	char* terrainClass::readFile(const char* fileName, int& size) {
		FILE* f = NULL;

		errno_t err = fopen_s(&f, fileName, "rb");

		// File does not open
		if (!f) {
			char buf[256] = { 0 };
			strerror_s(buf, sizeof(buf), err);
			printf("ERROR::TERRAIN::FILE_NOT_LOADED\n%s", buf);
			exit(0);
		}

		// Get file stats
		struct stat statBuf;
		int error = stat(fileName, &statBuf);

		if (error) {
			char buf[256] = { 0 };
			strerror_s(buf, sizeof(buf), err);
			printf("ERROR::TERRAIN::FILE_STATS\n%s", buf);
			return NULL;
		}

		// Read file
		char* p = (char*)malloc(size); // will be deallocated by Array2D
		assert(p);

		size_t bytesRead = fread(p, 1, size, f);

		// Check if file was read
		if (bytesRead != size) {
			char buf[256] = { 0 };
			strerror_s(buf, sizeof(buf), err);
			printf("ERROR:TERRAIN::FILE_NOT_READ\n%s", buf);
			exit(0);
		}

		fclose(f);

		return p;
	}
}