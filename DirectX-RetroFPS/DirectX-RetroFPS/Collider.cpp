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