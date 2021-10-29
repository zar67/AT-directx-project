#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Transform.h"

class Collider
{
public:
	struct ColliderVertex
	{
		DirectX::XMFLOAT3 Vertex;
		DirectX::XMFLOAT3 Normal;
	};
public:
	Collider() = default;
	~Collider() = default;

	void SetTransform(Transform& transform);
	void SetColliderData(std::vector<ColliderVertex> data);

	std::vector<DirectX::XMFLOAT3> GetVertices();
	std::vector<DirectX::XMFLOAT3> GetNormals();

private:
	std::vector<DirectX::XMVECTOR> m_vertices;
	std::vector<DirectX::XMVECTOR> m_normals;

	Transform& m_pTransform;
};