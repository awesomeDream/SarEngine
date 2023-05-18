#pragma once

class Vector2
{
public:
	float x, y;

public:
	Vector2(void);
	Vector2(float x, float y);
	Vector2(const Vector2& vec);
	~Vector2(void);

public:
	static Vector2 zero() { return { 0, 0 }; };
	static Vector2 e1() { return { 1, 0 }; };
	static Vector2 e2() { return { 0, 1 }; };
	static Vector2 one() { return { 1, 1 }; };

public:
	Vector2 operator+(const Vector2& vec) const;
	Vector2 operator-(const Vector2& vec) const;
	Vector2 operator*(const float scala) const;
	Vector2 operator/(const float scala) const;

	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const float scala);
	Vector2& operator/=(const float scala);

	bool operator==(const Vector2& vec);

public:
	static Vector2 lerp(const Vector2& a, const Vector2& b, const float& t);

	static float dot(const Vector2& vec1, const Vector2& vec2);

	Vector2 normalized(void) const;
	Vector2& normalize(void);

public:
	float magnitude(void) const;
	Vector2 copy() const;
};

class Vector3
{
public:
	float x, y, z;

public:
	Vector3(void);
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vec);
	~Vector3(void);

public:
	static Vector3 zero() { return { 0, 0, 0 }; };
	static Vector3 e1() { return { 1, 0, 0 }; };
	static Vector3 e2() { return { 0, 1, 0 }; };
	static Vector3 e3() { return { 0, 0, 1 }; };
	static Vector3 one() { return { 1, 1, 1 }; };

public:
	Vector3 operator+(const Vector3& vec) const;
	Vector3 operator-(const Vector3& vec) const;
	Vector3 operator*(const float scala) const;
	Vector3 operator/(const float scala) const;

	Vector3& operator+=(const Vector3& vec);
	Vector3& operator-=(const Vector3& vec);
	Vector3& operator*=(const float scala);
	Vector3& operator/=(const float scala);

	bool operator==(const Vector3& vec);

public:
	static Vector3 lerp(const Vector3& a, const Vector3& b, const float& t);

	static float dot(const Vector3& vec1, const Vector3& vec2);
	static Vector3 cross(const Vector3& vec1, const Vector3& vec2);

	Vector3 normalized(void) const;
	Vector3& normalize(void);

public:
	float magnitude(void) const;
	Vector3 copy() const;
};

class Vector4
{
public:
	float x, y, z, w;

public:
	Vector4(void);
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector3& vec);
	Vector4(const Vector4& vec);
	~Vector4(void);

public:
	static Vector4 zero() { return { 0, 0, 0, 0 }; };
	static Vector4 e1() { return { 1, 0, 0, 0 }; };
	static Vector4 e2() { return { 0, 1, 0, 0 }; };
	static Vector4 e3() { return { 0, 0, 1, 0 }; };
	static Vector4 e4() { return { 0, 0, 0, 1 }; };
	static Vector4 one() { return { 1, 1, 1, 1 }; };

public:
	Vector4 operator+(const Vector4& vec) const;
	Vector4 operator-(const Vector4& vec) const;
	Vector4 operator*(const float scala) const;
	Vector4 operator/(const float scala) const;

	Vector4& operator+=(const Vector4& vec);
	Vector4& operator-=(const Vector4& vec);
	Vector4& operator*=(const float scala);
	Vector4& operator/=(const float scala);

	bool operator==(const Vector4& vec);

public:
	static Vector4 lerp(const Vector4& a, const Vector4& b, const float& t);
	
	static float dot(const Vector4& vec1, const Vector4& vec2);

	Vector4 normalized(void) const;
	Vector4& normalize(void);

	Vector4 perspectiveDivision(void) const;

public:
	float magnitude(void) const;
	Vector4 copy() const;
};