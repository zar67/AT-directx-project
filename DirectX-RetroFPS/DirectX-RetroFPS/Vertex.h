/* ------------------------------------------------- */
/* Filename: Vertex.h                                */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Vertex struct.         */
/* ------------------------------------------------- */

#pragma once
#include <DirectXMath.h>

struct Vertex
{
	Vertex(float x, float y, float r, float g, float b);

	DirectX::XMFLOAT2 Position;
	DirectX::XMFLOAT3 Colour;
};