#pragma once

#include <DirectXMath.h>
#include "Vector.h"

struct Transform
{
	Vector Position;
	Vector Rotation;
	Vector Scale;

	bool ConstrainXPosition;
	bool ConstrainYPosition;
	bool ConstrainZPosition;

	bool ConstrainXRotation;
	bool ConstrainYRotation;
	bool ConstrainZRotation;

	Transform()
	{
		Position.Set(0.0f, 0.0f, 0.0f);
		Rotation.Set(0.0f, 0.0f, 0.0f);
		Scale.Set(1.0f, 1.0f, 1.0f);

		ConstrainXPosition = false;
		ConstrainYPosition = false;
		ConstrainZPosition = false;

		ConstrainXRotation = false;
		ConstrainYRotation = false;
		ConstrainZRotation = false;
	}

	DirectX::XMMATRIX GetTransformMatrix()
	{
		return DirectX::XMMatrixScaling(Scale.X, Scale.Y, Scale.Z) *
			DirectX::XMMatrixRotationRollPitchYaw(Rotation.X, Rotation.Y, Rotation.Z) *
			DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z);
	}

	DirectX::XMMATRIX GetTransformMatrixWithConstraints(bool rotationX, bool rotationY, bool rotationZ)
	{
		return DirectX::XMMatrixScaling(Scale.X, Scale.Y, Scale.Z) *
			DirectX::XMMatrixRotationRollPitchYaw(rotationX ? 0 : Rotation.X, rotationY ? 0 : Rotation.Y, rotationZ ? 0 : Rotation.Z) *
			DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z);
	}

	Vector ApplyTranslation(float x, float y, float z)
	{
		DirectX::XMFLOAT3 translation = DirectX::XMFLOAT3(x, y, z);

		DirectX::XMStoreFloat3(
			&translation,
			DirectX::XMVector3Transform(
				DirectX::XMLoadFloat3(&translation),
				DirectX::XMMatrixRotationRollPitchYaw(Rotation.X, Rotation.Y, Rotation.Z)
			));

		if (!ConstrainXPosition)
		{
			Position.X += translation.x;
		}
		if (!ConstrainYPosition)
		{
			Position.Y += translation.y;
		}
		if (!ConstrainZPosition)
		{
			Position.Z += translation.z;
		}

		return Vector(translation);
	}

	Vector ApplyTranslation(Vector translation)
	{
		return ApplyTranslation(translation.X, translation.Y, translation.Z);
	}

	void ApplyTranslationOnAxes(Vector translation)
	{
		if (!ConstrainXPosition)
		{
			Position.X += translation.X;
		}
		if (!ConstrainYPosition)
		{
			Position.Y += translation.Y;
		}
		if (!ConstrainZPosition)
		{
			Position.Z += translation.Z;
		}
	}

	void ApplyRotation(float x, float y, float z)
	{
		if (!ConstrainXRotation)
		{
			Rotation.X += x;
		}
		if (!ConstrainYRotation)
		{
			Rotation.Y += y;
		}
		if (!ConstrainZRotation)
		{
			Rotation.Z += z;
		}
	}

	void ApplyScalar(float x, float y, float z)
	{
		Scale.X *= x;
		Scale.Y *= y;
		Scale.Z *= z;
	}
};