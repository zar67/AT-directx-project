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

	DirectX::XMFLOAT3 aReflection = Reflect(aVelocity, data.BCollisionNormal);
	DirectX::XMFLOAT3 aMovement = DirectX::XMFLOAT3(
		aReflection.x * revertColliderARatio,
		aReflection.y * revertColliderARatio,
		aReflection.z * revertColliderARatio
	);

	DirectX::XMFLOAT3 bReflection = Reflect(bVelocity, data.ACollisionNormal);
	DirectX::XMFLOAT3 bMovement = DirectX::XMFLOAT3(
		bReflection.x * revertColliderBRatio,
		bReflection.y * revertColliderBRatio,
		bReflection.z * revertColliderBRatio
	);

	std::cout << "--------------------" << std::endl;
	std::cout << "A Vel: (" << aVelocity.x << "," << aVelocity.y << "," << aVelocity.z << "), B Vel: (" << bVelocity.x << "," << bVelocity.y << "," << bVelocity.z << ")" << std::endl;
	std::cout << "A Normal: (" << data.ACollisionNormal.x << "," << data.ACollisionNormal.y << "," << data.ACollisionNormal.z << "), B Normal: " << data.BCollisionNormal.x << "," << data.BCollisionNormal.y << "," << data.BCollisionNormal.z << ")" << std::endl;
	std::cout << "A Move: (" << aMovement.x << "," << aMovement.y << "," << aMovement.z << "), B Move: (" << bMovement.x << "," << bMovement.y << "," << bMovement.z << ")" << std::endl;

	data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
	data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);
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

DirectX::XMFLOAT3 CollisionUtilities::Reflect(DirectX::XMFLOAT3 vector, DirectX::XMFLOAT3 normal)
{
	float normalLength = sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2));
	DirectX::XMFLOAT3 normalisedNormal = DirectX::XMFLOAT3(
		normal.x / normalLength,
		normal.y / normalLength,
		normal.z / normalLength
	);

	float dotProduct = DotProduct(vector, normalisedNormal);

	DirectX::XMFLOAT3 finalReflection = DirectX::XMFLOAT3(
		vector.x - (2 * dotProduct * normalisedNormal.x),
		vector.y - (2 * dotProduct * normalisedNormal.y),
		vector.z - (2 * dotProduct * normalisedNormal.z)
	);

	return finalReflection;
}
