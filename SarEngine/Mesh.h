#pragma once

#include <regex>
#include <fstream>
#include <strstream>

#include "Stack.h"

struct VertexArray {
	float* array = nullptr;
	size_t size = 0;
};

struct IndexArray {
	int* array = nullptr;
	size_t size = 0;
};

class Mesh
{
private:
	VertexArray vArray;
	IndexArray iArray;

public:
	Mesh();
	~Mesh();

public:
	const VertexArray* getVertexArray() const { return &this->vArray; }
	const IndexArray* getIndexArray() const { return &this->iArray; }

public:
	bool loadObjFile(const char* fileName);
	void loadCube(void);
};