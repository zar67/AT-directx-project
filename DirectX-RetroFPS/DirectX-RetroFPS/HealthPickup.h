#pragma once

#include "Pickup.h"

class HealthPickup : public Pickup
{
public:
	HealthPickup(Graphics& graphics, Player& player);

	virtual void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other) override;
private:
	float m_healAmount = 10.0f;
};