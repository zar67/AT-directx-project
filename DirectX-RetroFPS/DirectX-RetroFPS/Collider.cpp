#include "Collider.h"

void Collider::SetTransform(Transform* transform)
{
	m_pTransform = transform;
}

void Collider::SetColliderData(std::vector<ColliderVertex> data)
{
	for (ColliderVertex& vertexData : data)
	{
		DirectX::XMFLOAT3 vertex = vertexData.Vertex.AsFLOAT3();
		m_vertices.push_back(DirectX::XMLoadFloat3(&vertex));

		DirectX::XMFLOAT3 normal = vertexData.Normal.AsFLOAT3();
		m_normals.push_back(DirectX::XMLoadFloat3(&normal));
	}
}

void Collider::SetRotationConstraints(bool x, bool y, bool z)
{
	m_constrainXRotation = x;
	m_constrainYRotation = y;
	m_constrainZRotation = y;
}

void Collider::SetStatic(bool value)
{
	m_isStatic = value;
}

std::vector<Vector> Collider::GetVertices()
{
	std::vector<Vector> multipliedVertices;

	for (DirectX::XMVECTOR vertex : m_vertices)
	{
		DirectX::XMVECTOR convertedVertex = DirectX::XMVector3Transform(vertex, m_pTransform->GetTransformMatrixWithConstraints(m_constrainXRotation, m_constrainYRotation, m_constrainZRotation));
		DirectX::XMFLOAT3 convertexVertexFloat;

		DirectX::XMStoreFloat3(&convertexVertexFloat, convertedVertex);

		multipliedVertices.push_back(Vector(convertexVertexFloat));
	}

	return multipliedVertices;
}

std::vector<Vector> Collider::GetNormals()
{
	std::vector<Vector> multipliedNormals;

	for (DirectX::XMVECTOR normal : m_normals)
	{
		DirectX::XMVECTOR convertedNormal = DirectX::XMVector3TransformNormal(normal, m_pTransform->GetTransformMatrixWithConstraints(m_constrainXRotation, m_constrainYRotation, m_constrainZRotation));
		DirectX::XMFLOAT3 convertexNormalFloat;

		DirectX::XMStoreFloat3(&convertexNormalFloat, convertedNormal);
		multipliedNormals.push_back(Vector(convertexNormalFloat));
	}

	return multipliedNormals;
}

void Collider::IncreaseVelocity(float x, float y, float z)
{
	m_velocity.X += x;
	m_velocity.Y += y;
	m_velocity.Z += z;
}

void Collider::IncreaseVelocity(Vector value)
{
	m_velocity.X += value.X;
	m_velocity.Y += value.Y;
	m_velocity.Z += value.Z;
}

void Collider::ResetVelocity()
{
	m_velocity = Vector(0.0f, 0.0f, 0.0f);
}

bool Collider::IsStatic()
{
	return m_isStatic;
}

Vector Collider::GetVelocity()
{
	return m_velocity;
}

Transform* Collider::GetTransform()
{
	return m_pTransform;
}