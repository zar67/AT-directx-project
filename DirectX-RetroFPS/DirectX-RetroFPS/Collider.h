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

	void SetTransform(Transform* transform);
	void SetColliderData(std::vector<ColliderVertex> data);
	void SetRotationConstraints(bool x, bool y, bool z);
	void SetStatic(bool value);

	std::vector<DirectX::XMFLOAT3> GetVertices();
	std::vector<DirectX::XMFLOAT3> GetNormals();

	void IncreaseVelocity(float x, float y, float z);
	void IncreaseVelocity(DirectX::XMFLOAT3 value);
	void ResetVelocity();
	bool IsVelocityZero();
	bool IsStatic();

	DirectX::XMFLOAT3 GetVelocity();
	Transform* GetTransform();

private:
	std::vector<DirectX::XMVECTOR> m_vertices;
	std::vector<DirectX::XMVECTOR> m_normals;

	Transform* m_pTransform = nullptr;
	DirectX::XMFLOAT3 m_velocity;

	bool m_isStatic = false;

	bool m_constrainXRotation;
	bool m_constrainYRotation;
	bool m_constrainZRotation;
};