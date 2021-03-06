#include "BulletPickup.h"
#include "SoundManager.h"

BulletPickup::BulletPickup(Graphics& graphics, Player& player, WeaponType type, int bulletNumber) : Pickup(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\pickups.png", 4, 3);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_bulletAmount = bulletNumber;
	m_weaponType = type;

	m_spinningAnimation = Animation(m_pSpriteSheet, { 8, 9, 10, 11 }, 5);
}

void BulletPickup::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr)
	{
		if (player->GetWeaponOfType(m_weaponType) != nullptr)
		{
			player->GetWeaponOfType(m_weaponType)->AddBullets(m_bulletAmount);
			SoundManager::GetInstance().Play(SoundType::BULLET_PICKUP);
			SetActive(false);
		}
	}
}