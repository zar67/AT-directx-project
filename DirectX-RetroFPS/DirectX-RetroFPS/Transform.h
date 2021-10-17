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
			DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z) *
			DirectX::XMMatrixRotationRollPitchYaw(Rotation.Pitch, Rotation.Yaw, Rotation.Roll) *
			DirectX::XMMatrixScaling(Scale.X * (3.0f / 4.0f), Scale.Y, Scale.Z)
		);
	}
};