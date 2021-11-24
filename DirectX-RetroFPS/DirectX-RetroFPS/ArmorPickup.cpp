#include "ArmorPickup.h"
#include "SoundManager.h"

ArmorPickup::ArmorPickup(Graphics& graphics, Player& player) : Pickup(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\pickups.png", 4, 3);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_spinningAnimation = Animation(m_pSpriteSheet, { 4, 5, 6, 7 }, 5);
}

void ArmorPickup::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr)
	{
		if (player->GetArmor().GetCurrentValue() != player->GetArmor().GetMaxValue())
		{
			player->GetArmor().Increase(m_armorAmount);
			SoundManager::GetInstance().Play(SoundType::ITEM_PICKUP);
			SetActive(false);
		}
	}
}