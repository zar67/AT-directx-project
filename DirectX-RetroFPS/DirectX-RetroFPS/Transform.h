#pragma once

struct Position
{
	float X;
	float Y;
	float Z;

	Position()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}
};

struct Rotation
{
	float Pitch;
	float Yaw;
	float Roll;

	Rotation()
	{
		Pitch = 0;
		Yaw = 0;
		Roll = 0;
	}
};

struct Scale
{
	float X;
	float Y;
	float Z;

	Scale()
	{
		X = 1;
		Y = 1;
		Z = 1;
	}
};

struct Transform
{
	Position Position;
	Rotation Rotation;
	Scale Scale;

	DirectX::XMMATRIX TransposeMatrix()
	{
		return DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationX(Rotation.Pitch) *
			DirectX::XMMatrixRotationY(Rotation.Yaw) *
			DirectX::XMMatrixRotationZ(Rotation.Roll) *
			DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z) *
			DirectX::XMMatrixScaling(Scale.X, Scale.Y, Scale.Z) * 
			DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f/4.0f, 0.5, 10.0f)
		);
	}

	void Move(float x, float y, float z)
	{
		Position.X += x;
		Position.Y += y;
		Position.Z += z;
	}
};