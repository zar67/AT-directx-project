#pragma once

#include "Ray.h"
#include "CollisionUtilities.h"
#include "DrawableBase.h"

class Shooter
{
public:
	Shooter() = default;

	void SetDamage(float damage);
	void SetParent(DrawableBase* drawable);

	void StartShoot(Ray ray);
	void RegisterCollision(CollisionUtilities::RayCollision collision, DrawableBase* drawable);
	void HandleHit();

	Ray& GetShootRay();

private:
	Ray m_shootRay = Ray();

	CollisionUtilities::RayCollision m_nearestCollision;
	DrawableBase* m_nearestCollisionDrawable = nullptr;

	float m_damage;
	DrawableBase* m_pParent = nullptr;
};