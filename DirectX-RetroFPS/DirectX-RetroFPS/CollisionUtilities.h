#pragma once

#include "OBBCollider.h"
#include "Ray.h"

static class CollisionUtilities
{
public:
	struct CollisionData
	{
		bool IsColliding;
		OBBCollider* ColliderA;
		OBBCollider* ColliderB;
		float Separation;
		Vector ACollisionNormal;
		Vector BCollisionNormal;

		CollisionData()
		{
			IsColliding = false;
			ColliderA = nullptr;
			ColliderB = nullptr;
			Separation = 0;
			ACollisionNormal = Vector();
			BCollisionNormal = Vector();
		}
	};
public:
	static bool IsCollisionPossible(OBBCollider& colliderOne, OBBCollider& colliderTwo);
	static CollisionData IsColliding(OBBCollider& colliderOne, OBBCollider& colliderTwo);
    
	static bool IsCollisionPossible(Ray& ray, OBBCollider& collider);
	static bool IsColliding(Ray& ray, OBBCollider& collider);
    
	static void ResolveCollision(CollisionData data);
private:
	static CollisionData FindMinimumSeparation(OBBCollider& colliderOne, OBBCollider& colliderTwo);
};