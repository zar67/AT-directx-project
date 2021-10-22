/* ------------------------------------------------- */
/* Filename: Vertex.cpp                              */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the Vertex struct.                                */
/* ------------------------------------------------- */

#include "Vertex.h"

Vertex::Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 colour)
{
	Vertex(position, DirectX::XMFLOAT2(0, 0), colour);
}

Vertex::Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 textureCoords)
{
	Vertex(position, textureCoords, DirectX::XMFLOAT3(1, 1, 1));
}

Vertex::Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 textureCoords, DirectX::XMFLOAT3 colour)
{
	Position = position;
	TextureCoords = textureCoords;
	Colour = colour;
}