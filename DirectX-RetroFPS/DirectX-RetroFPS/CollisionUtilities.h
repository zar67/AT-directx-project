#pragma once

#include "OBBCollider.h"
#include "Ray.h"

static class CollisionUtilities
{
public:
	struct ColliderCollision
	{
		bool IsColliding;
		OBBCollider* ColliderA;
		OBBCollider* ColliderB;
		float Separation;
		Vector ACollisionNormal;
		Vector BCollisionNormal;

		ColliderCollision()
		{
			IsColliding = false;
			ColliderA = nullptr;
			ColliderB = nullptr;
			Separation = 0;
			ACollisionNormal = Vector();
			BCollisionNormal = Vector();
		}
	};

	struct RayCollision
	{
		bool IsColliding;
		Ray CollisionRay;
		OBBCollider* Collider;
		Vector IntersectionPosition;
		float IntersectionDistance;

		RayCollision()
		{
			CollisionRay = Ray();
			Collider = nullptr;
			IntersectionPosition = Vector();
			IntersectionDistance = 0;
		};
	};

public:
	static bool IsCollisionPossible(OBBCollider& colliderOne, OBBCollider& colliderTwo);
	static ColliderCollision IsColliding(OBBCollider& colliderOne, OBBCollider& colliderTwo);
    
	static bool IsCollisionPossible(Ray& ray, OBBCollider& collider);
	static RayCollision IsColliding(Ray& ray, OBBCollider& collider);
    
	static void ResolveCollision(ColliderCollision data);
private:
	static ColliderCollision FindMinimumSeparation(OBBCollider& colliderOne, OBBCollider& colliderTwo);
};