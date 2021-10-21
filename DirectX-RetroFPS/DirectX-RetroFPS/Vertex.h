/* ------------------------------------------------- */
/* Filename: Vertex.h                                */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Vertex struct.         */
/* ------------------------------------------------- */

#pragma once
#include <DirectXMath.h>
#include "Transform.h"

struct Vertex
{
	Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 colour);
	Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 textureCoords);
	Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 textureCoords, DirectX::XMFLOAT3 colour);

	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 TextureCoords;
	DirectX::XMFLOAT3 Colour;
};