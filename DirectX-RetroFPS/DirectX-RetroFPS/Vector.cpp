#include "Vector.h"

Vector::Vector(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vector::Vector(const Vector& other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
}

Vector::Vector(DirectX::XMFLOAT3 other)
{
	X = other.x;
	Y = other.y;
	Z = other.z;
}

bool Vector::operator==(const Vector& other)
{
	return X == other.X && Y == other.Y && Z == other.Z;
}

Vector Vector::operator+(const Vector& other)
{
	return Vector(X + other.X, Y + other.Y, Z + other.Z);
}

Vector Vector::operator-(const Vector& other)
{
	return Vector(X - other.X, Y - other.Y, Z - other.Z);
}

Vector Vector::operator*(const Vector& other)
{
	return Vector(X * other.X, Y * other.Y, Z * other.Z);
}

Vector Vector::operator/(const Vector& other)
{
	return Vector(X / other.X, Y / other.Y, Z / other.Z);
}

void Vector::operator+=(const Vector& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
}

void Vector::operator-=(const Vector& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
}

void Vector::operator*=(const Vector& other)
{
	X *= other.X;
	Y *= other.Y;
	Z *= other.Z;
}

void Vector::operator/=(const Vector& other)
{
	X /= other.X;
	Y /= other.Y;
	Z /= other.Z;
}

Vector Vector::operator+(float scalar)
{
	return Vector(X + scalar, Y + scalar, Z + scalar);
}

Vector Vector::operator-(float scalar)
{
	return Vector(X - scalar, Y - scalar, Z - scalar);
}

Vector Vector::operator*(float scalar)
{
	return Vector(X * scalar, Y * scalar, Z * scalar);
}

Vector Vector::operator/(float scalar)
{
	return Vector(X / scalar, Y / scalar, Z / scalar);
}

void Vector::operator+=(float scalar)
{
	X += scalar;
	Y += scalar;
	Z += scalar;
}

void Vector::operator-=(float scalar)
{
	X -= scalar;
	Y -= scalar;
	Z -= scalar;
}

void Vector::operator*=(float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
}

void Vector::operator/=(float scalar)
{
	X /= scalar;
	Y /= scalar;
	Z /= scalar;
}

bool Vector::IsZero()
{
	return X == 0 && Y == 0 && Z == 0;
}

Vector Vector::GetNormalized()
{
	float scalar = GetMagnitude();

	if (scalar == 0)
	{
		return Vector(0.0f, 0.0f, 0.0f);
	}

	return Vector(
		X / scalar,
		Y / scalar,
		Z / scalar
	);
}

Vector Vector::GetReversed()
{
	return Vector(X * -1.0f, Y * -1.0f, Z * -1.0f);
}

float Vector::GetMagnitude()
{
	return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
}

float Vector::GetMagnitudeSquared()
{
	return pow(X, 2) + pow(Y, 2) + pow(Z, 2);
}

void Vector::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

DirectX::XMFLOAT3 Vector::AsFLOAT3()
{
	return DirectX::XMFLOAT3(X, Y, Z);
}

DirectX::XMVECTOR Vector::AsXMVector()
{
	DirectX::XMFLOAT3 asFloat = AsFLOAT3();
	return DirectX::XMLoadFloat3(&asFloat);
}

float Vector::DotProduct(Vector a, Vector b)
{
	return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

Vector Vector::CrossProduct(Vector a, Vector b)
{
	return Vector(
		(a.Y * b.Z) - (a.Z * b.Y),
		(a.Z * b.X) - (a.X * b.Z),
		(a.X * b.Y) - (a.Y * b.X)
	);
}