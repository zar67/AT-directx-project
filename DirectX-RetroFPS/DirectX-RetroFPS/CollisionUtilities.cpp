#include "CollisionUtilities.h"

CollisionUtilities::CollisionData CollisionUtilities::IsColliding(Collider& colliderOne, Collider& colliderTwo)
{
	CollisionUtilities::CollisionData returnData;

	float oneToTwoSeparation = FindMinimumSeparation(colliderOne, colliderTwo);
	float twoToOneSeparation = FindMinimumSeparation(colliderTwo, colliderOne);

	if (oneToTwoSeparation <= 0 && twoToOneSeparation <= 0)
	{
		returnData.IsColliding = true;
		returnData.ColliderA = &colliderOne;
		returnData.ColliderB = &colliderTwo;
		returnData.Separation = std::min(oneToTwoSeparation, twoToOneSeparation);
		
		return returnData;
	}

	returnData.IsColliding = false;
	return returnData;
}

void CollisionUtilities::ResolveCollision(CollisionUtilities::CollisionData data)
{
	DirectX::XMFLOAT3 aVelocity = data.ColliderA->GetVelocity();
	DirectX::XMFLOAT3 bVelocity = data.ColliderB->GetVelocity();

	// Calculate the ratio to push back each collider by
	float revertColliderARatio = 0.0f;
	float revertColliderBRatio = 0.0f;

	data.Separation = -data.Separation;

	if (data.ColliderA->IsVelocityZero() && !data.ColliderB->IsVelocityZero())
	{
		revertColliderBRatio = 1.0f;
	}
	else if (data.ColliderB->IsVelocityZero() && !data.ColliderA->IsVelocityZero())
	{
		revertColliderARatio = 1.0f;
	}
	else if (data.ColliderB->IsVelocityZero() && data.ColliderA->IsVelocityZero())
	{
		revertColliderARatio = 0.5f;
		revertColliderBRatio = 0.5f;
	}
	else
	{
		float aMagnitude = sqrt(pow(aVelocity.x, 2) + pow(aVelocity.y, 2) + pow(aVelocity.z, 2));
		float bMagnitude = sqrt(pow(bVelocity.x, 2) + pow(bVelocity.y, 2) + pow(bVelocity.z, 2));

		revertColliderARatio = (bMagnitude / (aMagnitude + bMagnitude));
		revertColliderBRatio = (aMagnitude / (aMagnitude + bMagnitude));
	}

	DirectX::XMFLOAT3 aMovement = DirectX::XMFLOAT3(-aVelocity.x * revertColliderARatio, -aVelocity.y * revertColliderARatio, -aVelocity.z * revertColliderARatio);
	DirectX::XMFLOAT3 bMovement = DirectX::XMFLOAT3(-bVelocity.x * revertColliderBRatio, -bVelocity.y * revertColliderBRatio, -bVelocity.z * revertColliderBRatio);

	data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
	data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);

	// Push back colliders by the reverse of their movement.
}

float CollisionUtilities::FindMinimumSeparation(Collider& colliderOne, Collider& colliderTwo)
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

float CollisionUtilities::DotProduct(DirectX::XMFLOAT3 vectorOne, DirectX::XMFLOAT3 vectorTwo)
{
	return (vectorOne.x * vectorTwo.x) + (vectorOne.y * vectorTwo.y) + (vectorOne.z * vectorTwo.z);
}
