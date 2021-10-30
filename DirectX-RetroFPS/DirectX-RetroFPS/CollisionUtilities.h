#pragma once

#include "Collider.h"

static class CollisionUtilities
{
public:
	struct CollisionData
	{
		bool IsColliding;
		Collider* ColliderA;
		Collider* ColliderB;
		float Separation;

		CollisionData()
		{
			IsColliding = false;
			ColliderA = nullptr;
			ColliderB = nullptr;
			Separation = 0;
		}
	};
public:
	static CollisionData IsColliding(Collider& colliderOne, Collider& colliderTwo);
	static void ResolveCollision(CollisionData data);
private:
	static float FindMinimumSeparation(Collider& colliderOne, Collider& colliderTwo);
	static float DotProduct(DirectX::XMFLOAT3 vectorOne, DirectX::XMFLOAT3 vectorTwo);
};