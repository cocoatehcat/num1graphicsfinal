#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <cerrno>
#include <sys/stat.h>
#include <cmath>

#include "terrain.h"


// Loads a heightmap for the program
void terrainClass::loadHeightMap(const char* fileName) {
	int fileSize = 0;
	unsigned char* p = (unsigned char*)readFile(fileName, fileSize);

	if (fileSize % sizeof(float) != 0) {
		printf("%s:%d - '%s' does not contain an whole number of floats (size %d)\n", __FILE__, __LINE__, fileName, fileSize);
		exit(0);
	}

	terrainSize = sqrtf(fileSize / sizeof(float));

	printf("Terrain size %d\n", terrainSize);

	if ((terrainSize * terrainSize) != (fileSize / sizeof(float))) {
		printf("%s:%d - '%s' does not contain a square height map - size %d\n", __FILE__, __LINE__, fileName, fileSize);
		exit(0);
	}

	// Uses terrainSize for height and width
	heightMap.InitArray2D(terrainSize, terrainSize, p);

	//heightMap.PrintFloat();
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

void terrainClass::initTerrain() {
	terrSh.genShader();
}

void terrainClass::loadHeightMapFile(const char* fileName) {
	loadHeightMap(fileName);

	triListOb.createTriList(terrainSize, terrainSize, this);
}

void terrainClass::Render() {
	initTerrain();
	terrSh.use();
	triListOb.Render();
}
