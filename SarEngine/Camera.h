#pragma once

#include "Axis.h"
#include "Matrix.h"
#include "Vector.h"

class Camera
{
private:
	Matrix4x4 projectionMatrix;
	Vector3 position;
	Axis axis;

private:
	float nearZ, farZ, aspect, fov, width, height;

public:
	Camera(float nearZ, float farZ, float fov, float width, float height);
	~Camera();

public:
	float getWidth(void) const { return this->width; };
	float getHeight(void) const { return this->height; };

public:
	void lookAt(const Vector3& up, const Vector3& vec);

	void SetPosition(const Vector3& vec) { this->position = vec; };
	void AddPosition(const Vector3& vec) { this->position += vec; };
	Vector3 GetPosition(void) const { return this->position; };

	void SetAxis(const Axis& axis) { this->axis = axis; };
	Axis GetAxis(void) const { return this->axis; };

	float getNear(void) const { return this->nearZ; }
	float getFar(void) const { return this->farZ; }

private:
	void setProjectionMatrix(void);
public:
	Matrix4x4 getProjectionMatrix(void) const;

public:

};