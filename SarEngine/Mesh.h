#pragma once

struct VertexArray {
	float* array = nullptr;
	size_t size;
};

struct IndexArray {
	int* array = nullptr;
	size_t size;
};

class Mesh
{
private:
	VertexArray vArray;
	IndexArray iArray;
public:
	Mesh()
	{

	}
	~Mesh()
	{
		if (this->vArray.array != nullptr)
			delete this->vArray.array;
		if (this->iArray.array != nullptr)
			delete this->iArray.array;
	}

	const VertexArray* getVertexArray() const { return &this->vArray; }
	const IndexArray* getIndexArray() const { return &this->iArray; }

	void loadCube()
	{
		this->vArray.size = 8;
		this->vArray.array = new float[8 * 3]
		{
			 1.f, -1.f, -1.f,
			 1.f, -1.f,  1.f,
			-1.f, -1.f,  1.f,
			-1.f, -1.f, -1.f,
			 1.f,  1.f, -1.f,
			 1.f,  1.f,  1.f,
			-1.f,  1.f,  1.f,
			-1.f,  1.f, -1.f,
		};

		this->iArray.size = 12;
		this->iArray.array = new int[12 * 3]
		{
			1, 2, 3,
			7, 6, 5,
			4, 5, 1,
			5, 6, 2,
			2, 6, 7,
			0, 3, 7,
			0, 1, 3,
			4, 7, 5,
			0, 4, 1,
			1, 5, 2,
			3, 2, 7,
			4, 0, 7,
		};
	}
};