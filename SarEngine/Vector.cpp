#include "Vector.h"
#include <cmath>

Vector2::Vector2(void)
{
	this->x = 0.f;
	this->y = 0.f;
}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2::Vector2(const Vector2& vec)
{
	this->x = vec.x;
	this->y = vec.y;
}
Vector2::~Vector2(void)
{

}

Vector2 Vector2::operator+(const Vector2& vec) const
{
	return { this->x + vec.x, this->y + vec.y };
}
Vector2 Vector2::operator-(const Vector2& vec) const
{
	return { this->x - vec.x, this->y - vec.y };
}
Vector2 Vector2::operator*(const float scala) const
{
	return { this->x * scala, this->y * scala };
}
Vector2 Vector2::operator/(const float scala) const
{
	if (scala == 0.f) throw "ERROR::Vector2 [ Zero Division (operator/) ]";
	return { this->x / scala, this->y / scala };
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}
Vector2& Vector2::operator-=(const Vector2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}
Vector2& Vector2::operator*=(float scala)
{
	this->x *= scala;
	this->y *= scala;

	return *this;
}
Vector2& Vector2::operator/=(float scala) {
	if (scala == 0.f) throw "ERROR::Vector2 [ Zero Division (operator/=) ]";

	this->x /= scala;
	this->y /= scala;

	return *this;
}

bool Vector2::operator==(const Vector2& vec)
{
	return (this->x == vec.x && this->y == vec.y);
}

float Vector2::dot(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

Vector2 Vector2::normalized() const
{
	float mag = sqrtf(this->x * this->x + this->y * this->y);
	if (mag == 0.f) throw "ERROR::Vector2 [ Zero Division (normalized) ]";

	return { this->x / mag, this->y / mag };
}
Vector2& Vector2::normalize()
{
	float mag = sqrtf(this->x * this->x + this->y * this->y);
	if (mag == 0.f) throw "ERROR::Vector2 [ Zero Division (normalize) ]";

	this->x /= mag;
	this->y /= mag;

	return *this;
}

float Vector2::magnitude() const
{
	return sqrtf(this->x * this->x + this->y * this->y);
}

Vector2 Vector2::copy() const {
	return { this->x, this->y };
}


Vector3::Vector3(void)
{
	this->x = 0.f;
	this->y = 0.f;
	this->z = 0.f;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3::Vector3(const Vector3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}
Vector3::~Vector3(void)
{

}

Vector3 Vector3::operator+(const Vector3& vec) const
{
	return { this->x + vec.x, this->y + vec.y, this->z + vec.z };
}
Vector3 Vector3::operator-(const Vector3& vec) const
{
	return { this->x - vec.x, this->y - vec.y, this->z - vec.z };
}
Vector3 Vector3::operator*(const float scala) const
{
	return { this->x * scala, this->y * scala, this->z * scala };
}
Vector3 Vector3::operator/(const float scala) const
{
	if (scala == 0.f) throw "ERROR::Vector3 [ Zero Division (operator/) ]";
	return { this->x / scala, this->y / scala, this->z / scala };
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;

	return *this;
}
Vector3& Vector3::operator-=(const Vector3& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;

	return *this;
}
Vector3& Vector3::operator*=(float scala)
{
	this->x *= scala;
	this->y *= scala;
	this->z *= scala;

	return *this;
}
Vector3& Vector3::operator/=(float scala) {
	if (scala == 0.f) throw "ERROR::Vector3 [ Zero Division (operator/=) ]";

	this->x /= scala;
	this->y /= scala;
	this->z /= scala;

	return *this;
}

bool Vector3::operator==(const Vector3& vec)
{
	return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
}

float Vector3::dot(const Vector3& vec1, const Vector3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
Vector3 Vector3::cross(const Vector3& vec1, const Vector3& vec2)
{
	return {
		vec1.y * vec2.z - vec1.z * vec2.y,
		vec1.z * vec2.x - vec1.x * vec2.z,
		vec1.x * vec2.y - vec1.y * vec2.x
	};
}

Vector3 Vector3::normalized() const
{
	float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	if (mag == 0.f) throw "ERROR::Vector3 [ Zero Division (normalized) ]";

	return { this->x / mag, this->y / mag, this->z / mag };
}
Vector3& Vector3::normalize()
{
	float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	if (mag == 0.f) throw "ERROR::Vector3 [ Zero Division (normalize) ]";

	this->x /= mag;
	this->y /= mag;
	this->z /= mag;

	return *this;
}

float Vector3::magnitude() const
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::copy() const {
	return { this->x, this->y, this->z };
}


Vector4::Vector4(void)
{
	this->x = 0.f;
	this->y = 0.f;
	this->z = 0.f;
	this->w = 0.f;
}
Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4::Vector4(const Vector3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = 1;
}
Vector4::Vector4(const Vector4& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
}
Vector4::~Vector4(void)
{

}

Vector4 Vector4::operator+(const Vector4& vec) const
{
	return { this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w };
}
Vector4 Vector4::operator-(const Vector4& vec) const
{
	return { this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w };
}
Vector4 Vector4::operator*(const float scala) const
{
	return { this->x * scala, this->y * scala, this->z * scala, this->w * scala };
}
Vector4 Vector4::operator/(const float scala) const
{
	if (scala == 0.f) throw "ERROR::Vector4 [ Zero Division (operator/) ]";
	return { this->x / scala, this->y / scala, this->z / scala, this->w / scala };
}

Vector4& Vector4::operator+=(const Vector4& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;

	return *this;
}
Vector4& Vector4::operator-=(const Vector4& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;

	return *this;
}
Vector4& Vector4::operator*=(float scala)
{
	this->x *= scala;
	this->y *= scala;
	this->z *= scala;
	this->w *= scala;

	return *this;
}
Vector4& Vector4::operator/=(float scala) {
	if (scala == 0.f) throw "ERROR::Vector4 [ Zero Division (operator/=) ]";

	this->x /= scala;
	this->y /= scala;
	this->z /= scala;
	this->w /= scala;

	return *this;
}

bool Vector4::operator==(const Vector4& vec)
{
	return (this->x == vec.x && this->y == vec.y && this->z == vec.z && this->w == vec.w);
}

float Vector4::dot(const Vector4& vec1, const Vector4& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w + vec2.w;
}

Vector4 Vector4::normalized() const
{
	float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
	if (mag == 0.f) throw "ERROR::Vector4 [ Zero Division (normalized) ]";

	return { this->x / mag, this->y / mag, this->z / mag, this->w / mag };
}
Vector4& Vector4::normalize()
{
	float mag = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
	if (mag == 0.f) throw "ERROR::Vector4 [ Zero Division (normalize) ]";

	this->x /= mag;
	this->y /= mag;
	this->z /= mag;
	this->w /= mag;

	return *this;
}

Vector3 Vector4::perspectiveProjection(void) const
{
	if (this->w == 0.f) throw "ERROR::Vector4 [ Zero Division (perspectiveProjection) ]";

	return { this->x / this->w, this->y / this->w, this->z / this->w };
}

float Vector4::magnitude() const
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

Vector4 Vector4::copy() const {
	return { this->x, this->y, this->z, this->w };
}