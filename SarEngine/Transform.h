#pragma once

#include "Vector.h"

struct Transform
{
	Vector3 position{ 0, 0, 0 };
	Vector3 rotation{ 0, 0, 0 };
	Vector3 scale{ 1, 1, 1 };
};