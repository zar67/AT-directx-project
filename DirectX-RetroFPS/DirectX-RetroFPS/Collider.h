#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Transform.h"
#include "Vector.h"

class Collider
{
public:
	struct ColliderVertex
	{
		Vector Vertex;
		Vector Normal;
	};
public:
	Collider() = default;
	~Collider() = default;

	void SetTransform(Transform* transform);
	void SetColliderData(std::vector<ColliderVertex> data);
	void SetRotationConstraints(bool x, bool y, bool z);
	void SetStatic(bool value);

	std::vector<Vector> GetVertices();
	std::vector<Vector> GetNormals();

	void IncreaseVelocity(float x, float y, float z);
	void IncreaseVelocity(Vector value);
	void ResetVelocity();
	bool IsStatic();

	Vector GetVelocity();
	Transform* GetTransform();

private:
	std::vector<DirectX::XMVECTOR> m_vertices;
	std::vector<DirectX::XMVECTOR> m_normals;

	Transform* m_pTransform = nullptr;
	Vector m_velocity;

	bool m_isStatic = false;

	bool m_constrainXRotation = false;
	bool m_constrainYRotation = false;
	bool m_constrainZRotation = false;
};