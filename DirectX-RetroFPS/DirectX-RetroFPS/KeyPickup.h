#pragma once

#include "Pickup.h"

class KeyPickup : public Pickup
{
public:
	KeyPickup(Graphics& graphics, Player& player);

	virtual void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other) override;
};