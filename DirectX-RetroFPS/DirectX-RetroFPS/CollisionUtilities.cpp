#include "CollisionUtilities.h"
#include <iostream>

bool CollisionUtilities::IsCollisionPossible(OBBCollider& colliderOne, OBBCollider& colliderTwo)
{
	float distanceSquared = (colliderOne.GetTransform()->Position - colliderTwo.GetTransform()->Position).GetMagnitudeSquared();
	return distanceSquared < 5;
}

bool CollisionUtilities::IsCollisionPossible(Ray& ray, OBBCollider& collider)
{
	return Vector::DotProduct(ray.Direction, ray.Origin - collider.GetTransform()->Position) > 0;
}

CollisionUtilities::ColliderCollision CollisionUtilities::IsColliding(OBBCollider& colliderOne, OBBCollider& colliderTwo)
{
	CollisionUtilities::ColliderCollision abData = FindMinimumSeparation(colliderOne, colliderTwo);
	CollisionUtilities::ColliderCollision baData = FindMinimumSeparation(colliderTwo, colliderOne);

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

	return CollisionUtilities::ColliderCollision();
}

CollisionUtilities::RayCollision CollisionUtilities::IsColliding(Ray& ray, OBBCollider& collider)
{
	CollisionUtilities::RayCollision rayCollisionData;
	rayCollisionData.CollisionRay = ray;
	rayCollisionData.Collider = &collider;

	Vector colliderMinPos = collider.GetMinPoint();
	Vector colliderMaxPos = collider.GetMaxPoint();

	float txmin = (colliderMinPos.X - ray.Origin.X) / ray.Direction.X;
	float txmax = (colliderMaxPos.X - ray.Origin.X) / ray.Direction.X;

	float tmin = txmin;
	float tmax = txmax;

	if (tmin > tmax)
	{
		float temp = tmin;
		tmin = tmax;
		tmax = temp;
	}

	float tymin = (colliderMinPos.Y - ray.Origin.Y) / ray.Direction.Y;
	float tymax = (colliderMaxPos.Y - ray.Origin.Y) / ray.Direction.Y;

	if (tymin > tymax)
	{
		float temp = tymin;
		tymin = tymax;
		tymax = temp;
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		rayCollisionData.IsColliding = false;
		return rayCollisionData;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	float tzmin = (colliderMinPos.Z - ray.Origin.Z) / ray.Direction.Z;
	float tzmax = (colliderMaxPos.Z - ray.Origin.Z) / ray.Direction.Z;

	if (tzmin > tzmax)
	{
		float temp = tzmin;
		tzmin = tzmax;
		tzmax = temp;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		rayCollisionData.IsColliding = false;
		return rayCollisionData;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	rayCollisionData.IsColliding = true;
	rayCollisionData.IntersectionDistance = std::abs(tmin);
	rayCollisionData.IntersectionPosition = ray.Origin + (ray.Direction.GetNormalized() * std::abs(tmin));

	return rayCollisionData;
}

void CollisionUtilities::ResolveCollision(CollisionUtilities::ColliderCollision data)
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

CollisionUtilities::ColliderCollision CollisionUtilities::FindMinimumSeparation(OBBCollider& a, OBBCollider& b)
{
	CollisionUtilities::ColliderCollision returnData;
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