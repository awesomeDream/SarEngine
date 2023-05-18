#pragma once

#include "Vector.h"

class Matrix4x4
{
public:
	float mat[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

public:
	Matrix4x4(void);
	Matrix4x4(const Matrix4x4& m);
	~Matrix4x4(void);

	Matrix4x4 operator+(const Matrix4x4& m);
	Matrix4x4 operator*(const Matrix4x4& m);
	Matrix4x4 operator*(const float &scala);

	Vector4 operator*(const Vector4& vec);

	void Identity(void);
	// void transpose(void);
	// void Inverse(void);

	static Matrix4x4 scale(const Vector3& vec);
	static Matrix4x4 rotateX(float theta);
	static Matrix4x4 rotateY(float theta);
	static Matrix4x4 rotateZ(float theta);
	static Matrix4x4 translate(const Vector3& vec);
};