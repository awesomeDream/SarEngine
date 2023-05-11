#include "Matrix.h"

#include "Vector.h"
#include <cmath>

const float PI = acosf(-1);

Matrix4x4::Matrix4x4()
{

}
Matrix4x4::Matrix4x4(const Matrix4x4& m)
{
	for (int i = 0; i < 16; i++)
		this->mat[i] = m.mat[i];
}
Matrix4x4::~Matrix4x4()
{

}
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& m)
{
	Matrix4x4 temp{ };
	
	for (int i = 0; i < 16; i++)
		temp.mat[i] = this->mat[i] + m.mat[i];

	return temp;
}
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m)
{
	Matrix4x4 temp{ };

	for (int i = 0; i < 16; i++) {
		int r = (i >> 2) << 2, c = i & 3;

		temp.mat[i] =
			this->mat[r] * m.mat[c] +
			this->mat[r + 1] * m.mat[c + 4] +
			this->mat[r + 2] * m.mat[c + 8] +
			this->mat[r + 3] * m.mat[c + 12];
	}

	return temp;
}
Matrix4x4 Matrix4x4::operator*(const float &scala)
{
	Matrix4x4 temp{ };

	for (int i = 0; i < 16; i++)
		temp.mat[i] = this->mat[i] * scala;

	return temp;
}

Vector4 Matrix4x4::operator*(const Vector4& vec)
{
	Vector4 temp
	{
		this->mat[0] * vec.x +
		this->mat[1] * vec.y +
		this->mat[2] * vec.z +
		this->mat[3] * vec.w,

		this->mat[4] * vec.x +
		this->mat[5] * vec.y +
		this->mat[6] * vec.z +
		this->mat[7] * vec.w,

		this->mat[8] * vec.x +
		this->mat[9] * vec.y +
		this->mat[10] * vec.z +
		this->mat[11] * vec.w,

		this->mat[12] * vec.x +
		this->mat[13] * vec.y +
		this->mat[14] * vec.z +
		this->mat[15] * vec.w,
	};

	return temp;
}

Matrix4x4 Matrix4x4::scale(const Vector3& vec) {
	Matrix4x4 ret;
	ret.mat[0] = vec.x;
	ret.mat[5] = vec.y;
	ret.mat[10] = vec.z;

	return ret;
}
Matrix4x4 Matrix4x4::rotateX(float theta) {
	float s = sin(theta * PI / 180);
	float c = cos(theta * PI / 180);

	Matrix4x4 ret;
	ret.mat[5] = c;
	ret.mat[6] = -s;
	ret.mat[9] = s;
	ret.mat[10] = c;

	return ret;
}
Matrix4x4 Matrix4x4::rotateY(float theta) {
	float s = sin(theta * PI / 180);
	float c = cos(theta * PI / 180);

	Matrix4x4 ret;
	ret.mat[0] = c;
	ret.mat[2] = s;
	ret.mat[8] = -s;
	ret.mat[10] = c;

	return ret;
}
Matrix4x4 Matrix4x4::rotateZ(float theta) {
	float s = sin(theta * PI / 180);
	float c = cos(theta * PI / 180);

	Matrix4x4 ret;
	ret.mat[0] = c;
	ret.mat[1] = -s;
	ret.mat[4] = s;
	ret.mat[5] = c;

	return ret;
}
Matrix4x4 Matrix4x4::translate(const Vector3& vec) {
	Matrix4x4 ret;
	ret.mat[3] = vec.x;
	ret.mat[7] = vec.y;
	ret.mat[11] = vec.z;

	return ret;
}