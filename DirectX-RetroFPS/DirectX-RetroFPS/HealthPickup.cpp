#include "HealthPickup.h"
#include "SoundManager.h"

HealthPickup::HealthPickup(Graphics& graphics, Player& player) : Pickup(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\pickups.png", 4, 3);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_spinningAnimation = Animation(m_pSpriteSheet, { 0, 1, 2, 3 }, 5);
}

void HealthPickup::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr)
	{
		if (player->GetHealth().GetCurrentValue() != player->GetHealth().GetMaxValue())
		{
			player->GetHealth().Increase(m_healAmount);
			SoundManager::GetInstance().Play(SoundType::ITEM_PICKUP);
			SetActive(false);
		}
	}
}