#pragma once
#include <DirectXMath.h>

class Vector
{
public:
	Vector() = default;
	Vector(float x, float y, float z);
	Vector(const Vector& other);
	Vector(DirectX::XMFLOAT3 other);
	~Vector() = default;

	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	Vector operator*(const Vector& other);
	Vector operator/(const Vector& other);

	void operator+=(const Vector& other);
	void operator-=(const Vector& other);
	void operator*=(const Vector& other);
	void operator/=(const Vector& other);

	Vector operator+(float scalar);
	Vector operator-(float scalar);
	Vector operator*(float scalar);
	Vector operator/(float scalar);

	void operator+=(float scalar);
	void operator-=(float scalar);
	void operator*=(float scalar);
	void operator/=(float scalar);

	bool IsZero();
	Vector GetNormalized();
	float GetMagnitude();
	float GetMagnitudeSquared();

	void Set(float x, float y, float z);

	DirectX::XMFLOAT3 AsFLOAT3();

	static float DotProduct(Vector a, Vector b);
	static Vector CrossProduct(Vector a, Vector b);

	float X = 0;
	float Y = 0;
	float Z = 0;
};