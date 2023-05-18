#pragma once

#include "Transform.h"
#include "Mesh.h"

class Object
{
private:
	Transform transform;
	Mesh mesh;

public:
	Object()
	{
		this->mesh.loadCube();
	}
	~Object()
	{
		
	}

	Mesh *getMesh(void)
	{
		return &this->mesh;
	}

public:
	Vector3 getPosition(void) const { return this->transform.position; };
	Vector3 getRotation(void) const { return this->transform.rotation; };
	Vector3 getScale(void) const { return this->transform.scale; };

	void setPosition(const Vector3& position)
	{
		this->transform.position = position;
	};
	void setRotation(const Vector3& rotation)
	{
		this->transform.rotation = rotation;
	};
	void setScale(const Vector3& scale)
	{
		this->transform.scale = scale;
	};
};