#include "KeyPickup.h"

#include "TextureBindable.h"

KeyPickup::KeyPickup(Graphics& graphics, Player& player) : Pickup(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\UI\\key.png", 1, 1);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_spinningAnimation = Animation(m_pSpriteSheet, { 1 }, 5);
}

void KeyPickup::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{
	Player* player = dynamic_cast<Player*>(other);
	if (player != nullptr)
	{
		player->HasKey(true);
		SetActive(false);
	}
}