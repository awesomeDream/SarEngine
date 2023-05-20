#include "Mesh.h"

#include "Stack.h"

Mesh::Mesh()
{
	this->vArray.array = nullptr;
	this->iArray.array = nullptr;
}

Mesh::~Mesh()
{
	if (this->vArray.array != nullptr)
		delete this->vArray.array;
	if (this->iArray.array != nullptr)
		delete this->iArray.array;
}

bool Mesh::loadObjFile(const char* fileName)
{
	std::ifstream f{ fileName };
	if (!f.is_open()) return false;

	StackFloat vertices;
	StackInt indexes;

	char line[1024];
	int face[10];

	while (!f.eof())
	{
		f.getline(line, 1023);

		int idx = 1;
		while (line[idx] == ' ') idx++;

		switch (line[0]) {
		case 'f':
		{
			if (line[1] != ' ') break;

			int a, b = 0;
			while (true) {
				a = 0;
				while ('0' <= line[idx] && line[idx] <= '9') {
					a = a * 10 + line[idx] - '0';
					idx++;
				}

				face[b++] = a;
				while (line[idx] != ' ' && line[idx] != '\0') idx++;
				while (line[idx] == ' ' || line[idx] == '\0') idx++;
				if (line[idx - 1] == '\0') break;
			}

			for (int i = 0; i < b - 2; i++) {
				indexes.push(face[0] - 1);
				indexes.push(face[i + 1] - 1);
				indexes.push(face[i + 2] - 1);
			}
		} break;
		case 'v':
		{
			if (line[1] != ' ') break;

			float a, b;
			for (int i = 0; i < 3; i++) {
				a = 0.f, b = 1.f;
				if (line[idx] == '-') { idx++; b = -1.f; }

				while ('0' <= line[idx] && line[idx] <= '9') {
					a = a * 10.f + (float)(line[idx] - '0');
					idx++;
				}

				if (line[idx++] != '.') {
					vertices.push(a * b);
					continue;
				}

				while ('0' <= line[idx] && line[idx] <= '9') {
					a = a * 10.f + (float)(line[idx] - '0');
					b /= 10.f;
					idx++;
				}

				idx++;
				vertices.push(a * b);
			}
		} break;
		default:
			break;
		}
	}

	this->vArray.size = vertices.size() / 3;
	this->vArray.array = new float[this->vArray.size * 3];
	this->iArray.size = indexes.size() / 3;
	this->iArray.array = new int[this->iArray.size * 3];

	vertices.copyToArray(this->vArray.array);
	indexes.copyToArray(this->iArray.array);

	return true;
}

void Mesh::loadCube(void)
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