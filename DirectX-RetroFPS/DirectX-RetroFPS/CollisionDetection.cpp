#include "CollisionDetection.h"

bool CollisionDetection::IsColliding(Collider& colliderOne, Collider& colliderTwo)
{
	return FindMinimumSeparation(colliderOne, colliderTwo) <= 0 && 
		   FindMinimumSeparation(colliderTwo, colliderOne) <= 0;
}

float CollisionDetection::FindMinimumSeparation(Collider& colliderOne, Collider& colliderTwo)
{
	float separation = std::numeric_limits<float>::lowest();

	std::vector<DirectX::XMFLOAT3> colliderOneVertices = colliderOne.GetVertices();
	std::vector<DirectX::XMFLOAT3> colliderOneNormals = colliderOne.GetNormals();

	std::vector<DirectX::XMFLOAT3> colliderTwoVertices = colliderTwo.GetVertices();
	std::vector<DirectX::XMFLOAT3> colliderTwoNormals = colliderTwo.GetNormals();

	for (int i = 0; i < colliderOneVertices.size(); i++)
	{
		DirectX::XMFLOAT3 colliderOneVertex = colliderOneVertices[i];
		DirectX::XMFLOAT3 colliderOneNormal = colliderOneNormals[i];

		float minSeparation = std::numeric_limits<float>::max();

		for (int j = 0; j < colliderTwoVertices.size(); j++)
		{
			DirectX::XMFLOAT3 colliderTwoVertex = colliderTwoVertices[j];
			DirectX::XMFLOAT3 oneToTwoVector = DirectX::XMFLOAT3(
				colliderTwoVertex.x - colliderOneVertex.x,
				colliderTwoVertex.y - colliderOneVertex.y,
				colliderTwoVertex.z - colliderOneVertex.z
			);

			minSeparation = std::min(minSeparation, DotProduct(oneToTwoVector, colliderOneNormal));
		}

		if (minSeparation > separation)
		{
			separation = minSeparation;
		}
	}

	return separation;
}

float CollisionDetection::DotProduct(DirectX::XMFLOAT3 vectorOne, DirectX::XMFLOAT3 vectorTwo)
{
	return (vectorOne.x * vectorTwo.x) + (vectorOne.y * vectorTwo.y) + (vectorOne.z * vectorTwo.z);
}
