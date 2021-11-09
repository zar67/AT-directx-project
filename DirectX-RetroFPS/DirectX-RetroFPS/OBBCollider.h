#pragma once

#include <DirectXMath.h>
#include <vector>

#include "Transform.h"
#include "Vector.h"

class OBBCollider
{
public:
	struct ColliderVertex
	{
		Vector Vertex;
		Vector Normal;
	};
public:
	OBBCollider() = default;
	~OBBCollider() = default;

	void SetTransform(Transform* transform);
	void SetColliderData(Vector minPosition, Vector maxPosition);
	void SetRotationConstraints(bool x, bool y, bool z);
	void SetStatic(bool value);

	std::vector<Vector> GetFaceVertices();
	std::vector<Vector> GetFaceNormals();

	std::vector<Vector> GetTransformedAxes();
	float GetMinPositionOnAxis(int axisIndex);
	float GetMaxPositionOnAxis(int axisIndex);

	void IncreaseVelocity(float x, float y, float z);
	void IncreaseVelocity(Vector value);
	void ResetVelocity();
	bool IsStatic();

	Vector GetVelocity();
	Transform* GetTransform();

private:
	std::vector<Vector> m_faceVertices;
	std::vector<Vector> m_faceNormals;

	Vector m_extents;
	Vector m_minimumPosition;
	Vector m_maximumPosition;

	Transform* m_pTransform = nullptr;
	Vector m_velocity;

	bool m_isStatic = false;

	bool m_constrainXRotation = false;
	bool m_constrainYRotation = false;
	bool m_constrainZRotation = false;
};