#pragma once

#include "Ray.h"
#include "CollisionUtilities.h"
#include "DrawableBase.h"
#include "Weapon.h"

class Shooter
{
public:
	Shooter() = default;

	void SetDamage(float damage);
	void SetParent(DrawableBase* drawable);

	void StartShoot(Ray ray);
	void ClearShooter();
	void RegisterCollision(CollisionUtilities::RayCollision collision, DrawableBase* drawable);
	void HandleHit();

	bool CanShoot();
	bool IsShooting();
	Ray& GetShootRay();

	void SetWeapon(Weapon* weapon);

private:
	Ray m_shootRay = Ray();

	CollisionUtilities::RayCollision m_nearestCollision;
	DrawableBase* m_nearestCollisionDrawable = nullptr;

	Weapon* m_pWeapon = nullptr;

	float m_damage;
	DrawableBase* m_pParent = nullptr;
};