#pragma once
#include "Graphics.h"

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
		return DirectX::XMMatrixRotationX(Rotation.x) *
			DirectX::XMMatrixRotationY(Rotation.y) *
			DirectX::XMMatrixRotationZ(Rotation.z) *
			DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z) *
			DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	}

	DirectX::XMMATRIX GetViewProjectionTransformMatrix(Graphics& graphics)
	{
		return DirectX::XMMatrixRotationX(Rotation.x) *
			DirectX::XMMatrixRotationY(Rotation.y) *
			DirectX::XMMatrixRotationZ(Rotation.z) *
			DirectX::XMMatrixTranslation(Position.x, Position.y, Position.z) *
			DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z) *
			graphics.GetCamera()->GetViewMatrix() *
			graphics.GetCamera()->GetProjectionMatrix();
	}

	void ApplyTranslation(float x, float y, float z)
	{
		Position.x += x;
		Position.y += y;
		Position.z += z;
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