#include "Collider.h"

void Collider::SetTransform(Transform* transform)
{
	m_pTransform = transform;
}

void Collider::SetColliderData(std::vector<ColliderVertex> data)
{
	for (ColliderVertex vertexData : data)
	{
		m_vertices.push_back(DirectX::XMLoadFloat3(&vertexData.Vertex));
		m_normals.push_back(DirectX::XMLoadFloat3(&vertexData.Normal));
	}
}

std::vector<DirectX::XMFLOAT3> Collider::GetVertices()
{
	std::vector<DirectX::XMFLOAT3> multipliedVertices;

	for (DirectX::XMVECTOR vertex : m_vertices)
	{
		DirectX::XMVECTOR convertedVertex = DirectX::XMVector3Transform(vertex, m_pTransform->GetTransformMatrix());
		DirectX::XMFLOAT3 convertexVertexFloat;

		DirectX::XMStoreFloat3(&convertexVertexFloat, convertedVertex);

		multipliedVertices.push_back(convertexVertexFloat);
	}

	return multipliedVertices;
}

std::vector<DirectX::XMFLOAT3> Collider::GetNormals()
{
	std::vector<DirectX::XMFLOAT3> multipliedNormals;

	for (DirectX::XMVECTOR normal : m_normals)
	{
		DirectX::XMVECTOR convertedNormal = DirectX::XMVector3TransformNormal(normal, m_pTransform->GetTransformMatrix());
		DirectX::XMFLOAT3 convertexNormalFloat;

		DirectX::XMStoreFloat3(&convertexNormalFloat, convertedNormal);
		multipliedNormals.push_back(convertexNormalFloat);
	}

	return multipliedNormals;
}

void Collider::IncreaseVelocity(float x, float y, float z)
{
	m_velocity.x += x;
	m_velocity.y += y;
	m_velocity.z += z;
}

void Collider::IncreaseVelocity(DirectX::XMFLOAT3 value)
{
	m_velocity.x += value.x;
	m_velocity.y += value.y;
	m_velocity.z += value.z;
}

void Collider::ResetVelocity()
{
	m_velocity = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

bool Collider::IsVelocityZero()
{
	return m_velocity.x == 0.0f && m_velocity.y == 0.0f && m_velocity.z == 0.0f;
}

DirectX::XMFLOAT3 Collider::GetVelocity()
{
	return m_velocity;
}

Transform* Collider::GetTransform()
{
	return m_pTransform;
}
