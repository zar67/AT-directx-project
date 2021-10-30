#pragma once

#include <DirectXMath.h>

struct Transform
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT3 Rotation;
	DirectX::XMFLOAT3 Scale;

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
	}

	DirectX::XMMATRIX GetTransformMatrix()
	{
		return DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z) *
			DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z) *
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

		Position.x += translation.x;
		Position.y += translation.y;
		Position.z += translation.z;

		return translation;
	}

	DirectX::XMFLOAT3 ApplyTranslation(DirectX::XMFLOAT3 translation)
	{
		return ApplyTranslation(translation.x, translation.y, translation.z);
	}

	void ApplyTranslationOnAxes(DirectX::XMFLOAT3 translation)
	{
		Position.x += translation.x;
		Position.y += translation.y;
		Position.z += translation.z;
	}

	void ApplyRotation(float x, float y, float z)
	{
		Rotation.x += x;
		Rotation.y += y;
		Rotation.z += z;
	}

	void ApplyScalar(float x, float y, float z)
	{
		Scale.x *= x;
		Scale.y *= y;
		Scale.z *= z;
	}
};