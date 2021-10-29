#pragma once

#include "Collider.h"

static class CollisionDetection
{
public:
	static bool IsColliding(Collider& colliderOne, Collider& colliderTwo);
private:
	static float FindMinimumSeparation(Collider& colliderOne, Collider& colliderTwo);
	static float DotProduct(DirectX::XMFLOAT3 vectorOne, DirectX::XMFLOAT3 vectorTwo);
};