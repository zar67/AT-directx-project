#pragma once

#include <DirectXMath.h>

struct TextureCoordinate
{
	enum class Position
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

	TextureCoordinate() 
	{
		Position = Position::TOP_LEFT;
		Coordinate = DirectX::XMFLOAT2(0.0f, 0.0f);
	};

	TextureCoordinate(Position position, DirectX::XMFLOAT2 coordinate)
	{
		Position = position;
		Coordinate = coordinate;
	};

	Position Position;
	DirectX::XMFLOAT2 Coordinate;
};