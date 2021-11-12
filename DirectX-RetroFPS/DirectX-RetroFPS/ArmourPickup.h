#pragma once

#include "Pickup.h"

class ArmourPickup : public Pickup
{
public:
	ArmourPickup(Graphics& graphics, Player& player);

	virtual void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other) override;
private:
	float m_armourAmount = 10.0f;
};