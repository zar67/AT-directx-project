#include "CollisionUtilities.h"
#include <iostream>

bool CollisionUtilities::IsCollisionPossible(OBBCollider& colliderOne, OBBCollider& colliderTwo)
{
	float distanceSquared = (colliderOne.GetTransform()->Position - colliderTwo.GetTransform()->Position).GetMagnitudeSquared();
	return distanceSquared < 5;
}

CollisionUtilities::CollisionData CollisionUtilities::IsColliding(OBBCollider& colliderOne, OBBCollider& colliderTwo)
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
	Vector aVelocity = data.ColliderA->GetVelocity();
	Vector bVelocity = data.ColliderB->GetVelocity();

	data.Separation = abs(data.Separation);

	// Check stationary object against moving object
	if ((aVelocity.IsZero() || data.ColliderA->IsStatic()) && (!bVelocity.IsZero() || !data.ColliderB->IsStatic()))
	{
		Vector bMovement = data.ACollisionNormal * data.Separation;

		data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);
	}
	// Check stationary object against moving object
	else if ((bVelocity.IsZero() || data.ColliderB->IsStatic()) && (!aVelocity.IsZero() || !data.ColliderA->IsStatic()))
	{
		Vector aMovement = data.BCollisionNormal * data.Separation;

		data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
	}
	// Check stationary objects
	else if (bVelocity.IsZero() && aVelocity.IsZero())
	{
		Vector aMovement = data.BCollisionNormal * 0.5f * data.Separation;
		Vector bMovement = data.ACollisionNormal * 0.5f * data.Separation;

		data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
		data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);
	}
	// Check two moving objects
	else
	{
		float aMagnitude = aVelocity.GetMagnitude();
		float bMagnitude = bVelocity.GetMagnitude();

		float revertColliderARatio = (bMagnitude / (aMagnitude + bMagnitude));
		float revertColliderBRatio = (aMagnitude / (aMagnitude + bMagnitude));

		Vector aMovement = data.BCollisionNormal * revertColliderARatio * data.Separation;
		Vector bMovement = data.ACollisionNormal * revertColliderBRatio * data.Separation;

		data.ColliderA->GetTransform()->ApplyTranslationOnAxes(aMovement);
		data.ColliderB->GetTransform()->ApplyTranslationOnAxes(bMovement);
	}
}

CollisionUtilities::CollisionData CollisionUtilities::FindMinimumSeparation(OBBCollider& a, OBBCollider& b)
{
	CollisionUtilities::CollisionData returnData;
	returnData.ColliderA = &a;
	returnData.ColliderB = &b;

	float separation = std::numeric_limits<float>::lowest();

	std::vector<Vector> aVertices = a.GetFaceVertices();
	std::vector<Vector> aNormals = a.GetFaceNormals();

	std::vector<Vector> bVertices = b.GetFaceVertices();
	std::vector<Vector> bNormals = b.GetFaceNormals();

	for (int i = 0; i < aVertices.size(); i++)
	{
		Vector aVertex = aVertices[i];
		Vector aNormal = aNormals[i];

		float minSeparation = std::numeric_limits<float>::max();
		int bCollisionIndex = 0;

		for (int j = 0; j < bVertices.size(); j++)
		{
			Vector bVertex = bVertices[j];
			Vector bNormal = bNormals[j];

			Vector abVector = bVertex - aVertex;
			float dotProduct = Vector::DotProduct(abVector, aNormal);

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