#pragma once

#include "Application.h"
#include "Vector.h"
#include "Matrix.h"
#include "Object.h"
#include "Camera.h"

class Renderer
{
private:
	Camera* camera;

public:
	Renderer() {};
	~Renderer() {};

public:
	void setCamera(Camera* camera) { this->camera = camera; }
	
public:
	Matrix4x4 modelMatrix(const Object& object);
	Matrix4x4 viewMatrix(void);
	Matrix4x4 projectionMatrix(void);
	Matrix4x4 screenSpace(void);

public:
	void renderObject(Object& object, Application &app);
};