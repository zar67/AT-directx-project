#pragma once

#include "Pickup.h"

class ArmorPickup : public Pickup
{
public:
	ArmorPickup(Graphics& graphics, Player& player);

	virtual void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other) override;
private:
	float m_armorAmount = 10.0f;
};