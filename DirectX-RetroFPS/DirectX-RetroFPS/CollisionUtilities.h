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
		DirectX::XMFLOAT3 ACollisionNormal;
		DirectX::XMFLOAT3 BCollisionNormal;

		CollisionData()
		{
			IsColliding = false;
			ColliderA = nullptr;
			ColliderB = nullptr;
			Separation = 0;
			ACollisionNormal = DirectX::XMFLOAT3();
			BCollisionNormal = DirectX::XMFLOAT3();
		}
	};
public:
	static CollisionData IsColliding(Collider& colliderOne, Collider& colliderTwo);
	static void ResolveCollision(CollisionData data);
private:
	static CollisionData FindMinimumSeparation(Collider& colliderOne, Collider& colliderTwo);
	static float DotProduct(DirectX::XMFLOAT3 vectorOne, DirectX::XMFLOAT3 vectorTwo);
};