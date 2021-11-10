#pragma once

#include "OBBCollider.h"
#include "Ray.h"

static class CollisionUtilities
{
public:
	struct CollisionData
	{
		bool IsColliding;

		CollisionData()
		{
			IsColliding = false;
		}
	};

	struct ColliderCollision : CollisionData
	{
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

	struct RayCollision : CollisionData
	{
		Ray CollisionRay;
		OBBCollider* Collider;
		Vector RayEnterPosition;
		Vector RayExitPosition;

		RayCollision()
		{
			CollisionRay = Ray();
			Collider = nullptr;
			RayEnterPosition = Vector();
			RayExitPosition = Vector();
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