#pragma once

#include "Collider.h"
#include "Vector.h"

static class CollisionUtilities
{
public:
	struct CollisionData
	{
		bool IsColliding;
		Collider* ColliderA;
		Collider* ColliderB;
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
	static bool IsCollisionPossible(Collider& colliderOne, Collider& colliderTwo);
	static CollisionData IsColliding(Collider& colliderOne, Collider& colliderTwo);
	static void ResolveCollision(CollisionData data);
private:
	static CollisionData FindMinimumSeparation(Collider& colliderOne, Collider& colliderTwo);
};