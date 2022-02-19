#pragma once

#include "Pickup.h"
#include "WeaponType.h"

class BulletPickup : public Pickup
{
public:
	BulletPickup(Graphics& graphics, Player& player, WeaponType type, int bulletNumber);

	virtual void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other) override;
private:
	WeaponType m_weaponType;
	float m_bulletAmount = 10.0f;
};