#include "Camera.h"
#include "Math.h"
#include <cmath>

Camera::Camera(float nearZ, float farZ, float fov, float width, float height)
{
	this->position = Vector3::zero();

	this->nearZ = nearZ;
	this->farZ = farZ;

	this->height = height;
	this->width = width;
	this->aspect = width / height;

	this->fov = fov;

	this->setProjectionMatrix();
}
Camera::~Camera()
{

}

void Camera::setProjectionMatrix(void)
{
	this->projectionMatrix.Identity();

	float cot = 1 / tan(this->fov / 2);
	float q = (this->farZ + this->nearZ) / (this->nearZ - this->farZ);
	float p = (2 * this->nearZ * this->farZ) / (this->nearZ - this->farZ);

	this->projectionMatrix.mat[0] = cot / this->aspect;
	this->projectionMatrix.mat[5] = cot;
	this->projectionMatrix.mat[10] = q;
	this->projectionMatrix.mat[11] = p;
	this->projectionMatrix.mat[14] = -1;
	this->projectionMatrix.mat[15] = 0;
}
Matrix4x4 Camera::getProjectionMatrix(void) const
{
	return this->projectionMatrix;
}

void Camera::lookAt(const Vector3& up, const Vector3& vec)
{
	this->axis.z = (this->position - vec).normalize();
	this->axis.x = Vector3::cross(up, this->axis.z);
	this->axis.y = Vector3::cross(this->axis.x, this->axis.z);

	this->setProjectionMatrix();
}