#include "HealthPickup.h"

HealthPickup::HealthPickup(Graphics& graphics, Player& player) : Pickup(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\doom_power_ups.png", 8, 2);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_spinningAnimation = Animation(m_pSpriteSheet, { 1, 3, 5, 7 }, 5);
}

void HealthPickup::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr)
	{
		if (player->GetHealth().GetCurrentValue() <= player->GetHealth().GetMaxValue() - m_healAmount)
		{
			player->GetHealth().Increase(m_healAmount);
			SetActive(false);
		}
	}
}