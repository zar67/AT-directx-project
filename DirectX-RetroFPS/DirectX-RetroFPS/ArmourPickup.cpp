#include "ArmourPickup.h"

ArmourPickup::ArmourPickup(Graphics& graphics, Player& player) : Pickup(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\doom_power_ups.png", 8, 2);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_spinningAnimation = Animation(m_pSpriteSheet, { 8, 10, 12, 14 }, 5);
}

void ArmourPickup::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr)
	{
		if (player->GetArmour().GetCurrentValue() <= player->GetArmour().GetMaxValue() - m_armourAmount)
		{
			player->GetArmour().Increase(m_armourAmount);
			SetActive(false);
		}
	}
}