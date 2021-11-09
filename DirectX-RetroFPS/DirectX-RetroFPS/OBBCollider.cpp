#include "OBBCollider.h"

void OBBCollider::SetTransform(Transform* transform)
{
	m_pTransform = transform;
}

void OBBCollider::SetColliderData(Vector minPosition, Vector maxPosition)
{
	m_extents = maxPosition - minPosition;
	m_minimumPosition = minPosition;
	m_maximumPosition = maxPosition;

	m_faceVertices = {
		Vector(minPosition.X + m_extents.X / 2, minPosition.Y, minPosition.Z + m_extents.Z / 2),
		Vector(minPosition.X + m_extents.X / 2, minPosition.Y + m_extents.Y, minPosition.Z + m_extents.Z / 2),
		Vector(minPosition.X + m_extents.X / 2, minPosition.Y + m_extents.Y / 2, minPosition.Z),
		Vector(minPosition.X + m_extents.X / 2, minPosition.Y + m_extents.Y / 2, minPosition.Z + m_extents.Z),
		Vector(minPosition.X, minPosition.Y + m_extents.Y / 2, minPosition.Z + m_extents.Z / 2),
		Vector(minPosition.X + m_extents.X, minPosition.Y + m_extents.Y / 2, minPosition.Z + m_extents.Z / 2)
	};

	m_faceNormals = {
		Vector(0.0f, -1.0f, 0.0f),
		Vector(0.0f, 1.0f, 0.0f),
		Vector(0.0f, 0.0f, -1.0f),
		Vector(0.0f, 0.0f, 1.0f),
		Vector(-1.0f, 0.0f, 0.0f),
		Vector(1.0f, 0.0f, 0.0f)
	};
}

void OBBCollider::SetRotationConstraints(bool x, bool y, bool z)
{
	m_constrainXRotation = x;
	m_constrainYRotation = y;
	m_constrainZRotation = y;
}

void OBBCollider::SetStatic(bool value)
{
	m_isStatic = value;
}

std::vector<Vector> OBBCollider::GetFaceVertices()
{
	std::vector<Vector> multipliedVertices;

	for (Vector vertex : m_faceVertices)
	{
		DirectX::XMFLOAT3 vertexFloat = vertex.AsFLOAT3();
		DirectX::XMVECTOR convertedVertex = DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&vertexFloat), m_pTransform->GetTransformMatrixWithConstraints(m_constrainXRotation, m_constrainYRotation, m_constrainZRotation));
		
		DirectX::XMFLOAT3 convertexVertexFloat;
		DirectX::XMStoreFloat3(&convertexVertexFloat, convertedVertex);

		multipliedVertices.push_back(Vector(convertexVertexFloat));
	}

	return multipliedVertices;
}

std::vector<Vector> OBBCollider::GetFaceNormals()
{
	std::vector<Vector> multipliedNormals;

	for (Vector normal : m_faceNormals)
	{
		DirectX::XMFLOAT3 normalFloat = normal.AsFLOAT3();
		DirectX::XMVECTOR convertedNormal = DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&normalFloat), m_pTransform->GetTransformMatrixWithConstraints(m_constrainXRotation, m_constrainYRotation, m_constrainZRotation));
		DirectX::XMFLOAT3 convertexNormalFloat;

		DirectX::XMStoreFloat3(&convertexNormalFloat, convertedNormal);
		multipliedNormals.push_back(Vector(convertexNormalFloat));
	}

	return multipliedNormals;
}

Vector OBBCollider::GetMinPoint()
{
	DirectX::XMFLOAT3 posFloat = m_minimumPosition.AsFLOAT3();
	DirectX::XMVECTOR convertedPos = DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&posFloat), m_pTransform->GetTransformMatrixWithConstraints(m_constrainXRotation, m_constrainYRotation, m_constrainZRotation));

	DirectX::XMFLOAT3 convertedPosFloat;
	DirectX::XMStoreFloat3(&convertedPosFloat, convertedPos);

	return Vector(convertedPosFloat);
}

Vector OBBCollider::GetMaxPoint()
{
	DirectX::XMFLOAT3 posFloat = m_maximumPosition.AsFLOAT3();
	DirectX::XMVECTOR convertedPos = DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&posFloat), m_pTransform->GetTransformMatrixWithConstraints(m_constrainXRotation, m_constrainYRotation, m_constrainZRotation));

	DirectX::XMFLOAT3 convertedPosFloat;
	DirectX::XMStoreFloat3(&convertedPosFloat, convertedPos);

	return Vector(convertedPosFloat);
}

void OBBCollider::IncreaseVelocity(float x, float y, float z)
{
	m_velocity.X += x;
	m_velocity.Y += y;
	m_velocity.Z += z;
}

void OBBCollider::IncreaseVelocity(Vector value)
{
	m_velocity.X += value.X;
	m_velocity.Y += value.Y;
	m_velocity.Z += value.Z;
}

void OBBCollider::ResetVelocity()
{
	m_velocity = Vector(0.0f, 0.0f, 0.0f);
}

bool OBBCollider::IsStatic()
{
	return m_isStatic;
}

Vector OBBCollider::GetVelocity()
{
	return m_velocity;
}

Transform* OBBCollider::GetTransform()
{
	return m_pTransform;
}