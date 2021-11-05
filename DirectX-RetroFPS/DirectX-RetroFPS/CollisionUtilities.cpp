#include "CollisionUtilities.h"
#include <iostream>

CollisionUtilities::CollisionData CollisionUtilities::IsColliding(Collider& colliderOne, Collider& colliderTwo)
{
	CollisionUtilities::CollisionData abData = FindMinimumSeparation(colliderOne, colliderTwo);
	CollisionUtilities::CollisionData baData = FindMinimumSeparation(colliderTwo, colliderOne);

	if (abData.Separation < 0 && baData.Separation < 0)
	{
		if (baData.Separation < abData.Separation)
		{
			baData.IsColliding = true;
			return baData;
		}
		else
		{
			abData.IsColliding = true;
			return abData;
		}
	}

	return CollisionUtilities::CollisionData();
}

void CollisionUtilities::ResolveCollision(CollisionUtilities::CollisionData data)
{
	DirectX::XMFLOAT3 aVelocity = data.ColliderA->GetVelocity();
	DirectX::XMFLOAT3 bVelocity = data.ColliderB->GetVelocity();

	data.Separation = abs(data.Separation);

	// Check stationary object against moving object
	if ((data.ColliderA->IsVelocityZero() || data.ColliderA->IsStatic()) && (!data.ColliderB->IsVelocityZero() || !data.ColliderB->IsStatic()))
	{
		DirectX::XMFLOAT3 bMovement = DirectX::XMFLOAT3(
			data.ACollisionNormal.x * data.Separation,
			data.ACollisionNormal.y * data.Separation,
			data.ACollisionNormal.z * data.Separation
		);

		data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);
	}
	// Check stationary object against moving object
	else if ((data.ColliderB->IsVelocityZero() || data.ColliderB->IsStatic()) && (!data.ColliderA->IsVelocityZero() || !data.ColliderA->IsStatic()))
	{
		DirectX::XMFLOAT3 aMovement = DirectX::XMFLOAT3(
			data.BCollisionNormal.x * data.Separation,
			data.BCollisionNormal.y * data.Separation,
			data.BCollisionNormal.z * data.Separation
		);

		data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
	}
	// Check stationary objects
	else if (data.ColliderB->IsVelocityZero() && data.ColliderA->IsVelocityZero() )
	{
		DirectX::XMFLOAT3 aMovement = DirectX::XMFLOAT3(
			data.BCollisionNormal.x * 0.5f * data.Separation,
			data.BCollisionNormal.y * 0.5f * data.Separation,
			data.BCollisionNormal.z * 0.5f * data.Separation
		);

		DirectX::XMFLOAT3 bMovement = DirectX::XMFLOAT3(
			data.ACollisionNormal.x * 0.5f * data.Separation,
			data.ACollisionNormal.y * 0.5f * data.Separation,
			data.ACollisionNormal.z * 0.5f * data.Separation
		);

		data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
		data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);
	}
	// Check two moving objects
	else
	{
		float aMagnitude = sqrt(pow(aVelocity.x, 2) + pow(aVelocity.y, 2) + pow(aVelocity.z, 2));
		float bMagnitude = sqrt(pow(bVelocity.x, 2) + pow(bVelocity.y, 2) + pow(bVelocity.z, 2));

		float revertColliderARatio = (bMagnitude / (aMagnitude + bMagnitude));
		float revertColliderBRatio = (aMagnitude / (aMagnitude + bMagnitude));

		DirectX::XMFLOAT3 aMovement = DirectX::XMFLOAT3(
			data.BCollisionNormal.x * revertColliderARatio * data.Separation,
			data.BCollisionNormal.y * revertColliderARatio * data.Separation,
			data.BCollisionNormal.z * revertColliderARatio * data.Separation
		);

		DirectX::XMFLOAT3 bMovement = DirectX::XMFLOAT3(
			data.ACollisionNormal.x * revertColliderBRatio * data.Separation,
			data.ACollisionNormal.y * revertColliderBRatio * data.Separation,
			data.ACollisionNormal.z * revertColliderBRatio * data.Separation
		);

		data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
		data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);
	}
}

CollisionUtilities::CollisionData CollisionUtilities::FindMinimumSeparation(Collider& a, Collider& b)
{
	CollisionUtilities::CollisionData returnData;
	returnData.ColliderA = &a;
	returnData.ColliderB = &b;

	float separation = std::numeric_limits<float>::lowest();

	std::vector<DirectX::XMFLOAT3> aVertices = a.GetVertices();
	std::vector<DirectX::XMFLOAT3> aNormals = a.GetNormals();

	std::vector<DirectX::XMFLOAT3> bVertices = b.GetVertices();
	std::vector<DirectX::XMFLOAT3> bNormals = b.GetNormals();

	for (int i = 0; i < aVertices.size(); i++)
	{
		DirectX::XMFLOAT3 aVertex = aVertices[i];
		DirectX::XMFLOAT3 aNormal = aNormals[i];

		float minSeparation = std::numeric_limits<float>::max();
		int bCollisionIndex = 0;

		for (int j = 0; j < bVertices.size(); j++)
		{
			DirectX::XMFLOAT3 bVertex = bVertices[j];
			DirectX::XMFLOAT3 bNormal = bNormals[j];

			DirectX::XMFLOAT3 abVector = DirectX::XMFLOAT3(
				bVertex.x - aVertex.x,
				bVertex.y - aVertex.y,
				bVertex.z - aVertex.z
			);

			float dotProduct = DotProduct(abVector, aNormal);
			if (dotProduct < minSeparation)
			{
				minSeparation = dotProduct;
				bCollisionIndex = j;
			}
		}

		if (minSeparation > separation)
		{
			separation = minSeparation;

			returnData.ACollisionNormal = aNormal;
			returnData.BCollisionNormal = bNormals[bCollisionIndex];
		}
	}

	returnData.Separation = separation;
	return returnData;
}

float CollisionUtilities::DotProduct(DirectX::XMFLOAT3 vectorOne, DirectX::XMFLOAT3 vectorTwo)
{
	return (vectorOne.x * vectorTwo.x) + (vectorOne.y * vectorTwo.y) + (vectorOne.z * vectorTwo.z);
}