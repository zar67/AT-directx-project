/* ------------------------------------------------- */
/* Filename: Vertex.h                                */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Vertex struct.         */
/* ------------------------------------------------- */

#pragma once
#include <DirectXMath.h>

struct Vertex
{
	Vertex(float x, float y);

	DirectX::XMFLOAT2 Position;
};