#pragma once

#include <DirectXMath.h>

struct Transform
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT3 Rotation;
	DirectX::XMFLOAT3 Scale;

	bool ConstrainXPosition;
	bool ConstrainYPosition;
	bool ConstrainZPosition;

	bool ConstrainXRotation;
	bool ConstrainYRotation;
	bool ConstrainZRotation;

	Transform()
	{
		Position.x = 0;
		Position.y = 0;
		Position.z = 0;

		Rotation.x = 0;
		Rotation.y = 0;
		Rotation.z = 0;

		Scale.x = 1;
		Scale.y = 1;
		Scale.z = 1;

		ConstrainXPosition = false;
		ConstrainYPosition = false;
		ConstrainZPosition = false;

		ConstrainXRotation = false;
		ConstrainYRotation = false;
		ConstrainZRotation = false;
	}

	DirectX::XMMATRIX GetTransformMatrix()
	{
		return DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z) *
			DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z) *
			DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);
	}

	DirectX::XMMATRIX GetTransformMatrixWithConstraints(bool rotationX, bool rotationY, bool rotationZ)
	{
		return DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z) *
			DirectX::XMMatrixRotationRollPitchYaw(rotationX ? 0 : Rotation.x, rotationY ? 0 : Rotation.y, rotationZ ? 0 :Rotation.z) *
			DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z);
	}

	DirectX::XMFLOAT3 ApplyTranslation(float x, float y, float z)
	{
		DirectX::XMFLOAT3 translation = DirectX::XMFLOAT3(x, y, z);

		DirectX::XMStoreFloat3(
			&translation,
			DirectX::XMVector3Transform(
				DirectX::XMLoadFloat3(&translation),
				DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z)
			));

		if (!ConstrainXPosition)
		{
			Position.x += translation.x;
		}
		if (!ConstrainYPosition)
		{
			Position.y += translation.y;
		}
		if (!ConstrainZPosition)
		{
			Position.z += translation.z;
		}

		return translation;
	}

	DirectX::XMFLOAT3 ApplyTranslation(DirectX::XMFLOAT3 translation)
	{
		return ApplyTranslation(translation.x, translation.y, translation.z);
	}

	void ApplyTranslationOnAxes(DirectX::XMFLOAT3 translation)
	{
		if (!ConstrainXPosition)
		{
			Position.x += translation.x;
		}
		if (!ConstrainYPosition)
		{
			Position.y += translation.y;
		}
		if (!ConstrainZPosition)
		{
			Position.z += translation.z;
		}
	}

	void ApplyRotation(float x, float y, float z)
	{
		if (!ConstrainXRotation)
		{
			Rotation.x += x;
		}
		if (!ConstrainYRotation)
		{
			Rotation.y += y;
		}
		if (!ConstrainZRotation)
		{
			Rotation.z += z;
		}
	}

	void ApplyScalar(float x, float y, float z)
	{
		Scale.x *= x;
		Scale.y *= y;
		Scale.z *= z;
	}
};