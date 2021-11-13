#include "Zombie.h"

Zombie::Zombie(Graphics& graphics, Player& player) : Enemy(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\doom_zombie.png", 32, 5);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_pSpriteSheet->SetCoordsToSpriteAt(0, m_textureCoords);
	for (int i = 0; i < 4; i++)
	{
		m_vertices[i].TextureCoords = m_textureCoords[i].Coordinate;
	}

	m_animationMap = {
		{Enemy::EnemyState::IDLE, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 0, 8, 16, 24 }, 5)},
			{Enemy::FaceDirection::FORWARDS_LEFT, Animation(m_pSpriteSheet, { 1, 9, 17, 25 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 2, 10, 18, 26 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_LEFT, Animation(m_pSpriteSheet, { 3, 11, 19, 27 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, {4, 12, 20, 28 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_RIGHT, Animation(m_pSpriteSheet, { 5, 13, 21, 29 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 6, 14, 22, 30 }, 5)},
			{Enemy::FaceDirection::FORWARDS_RIGHT, Animation(m_pSpriteSheet, { 7, 15, 23, 31 }, 5)}
		}},
		{Enemy::EnemyState::MOVING, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 128, 136, 144, 152 }, 5)},
			{Enemy::FaceDirection::FORWARDS_LEFT, Animation(m_pSpriteSheet, { 129, 137, 145, 153 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 130, 138, 146, 154 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_LEFT, Animation(m_pSpriteSheet, { 131, 139, 147, 155 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 132, 140, 148, 156 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_RIGHT, Animation(m_pSpriteSheet, { 133, 141, 149, 157 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 134, 142, 150, 158 }, 5)},
			{Enemy::FaceDirection::FORWARDS_RIGHT, Animation(m_pSpriteSheet, { 135, 143, 151, 159 }, 5)}
		}},
		{Enemy::EnemyState::ATTACKING, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 64, 72 }, 5)},
			{Enemy::FaceDirection::FORWARDS_LEFT, Animation(m_pSpriteSheet, { 65, 73 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 66, 74 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_LEFT, Animation(m_pSpriteSheet, { 67, 75 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 68, 76 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_RIGHT, Animation(m_pSpriteSheet, { 69, 77 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 70, 78 }, 5)},
			{Enemy::FaceDirection::FORWARDS_RIGHT, Animation(m_pSpriteSheet, { 71, 79 }, 5)}
		}},
		{Enemy::EnemyState::DEATH, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 96, 104, 112, 120 }, 5)},
			{Enemy::FaceDirection::FORWARDS_LEFT, Animation(m_pSpriteSheet, { 97, 105, 113, 121 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 98, 106, 114, 122 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_LEFT, Animation(m_pSpriteSheet, { 99, 107, 115, 123 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 100, 108, 116, 124 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_RIGHT, Animation(m_pSpriteSheet, { 101, 109, 117, 125 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 102, 110, 118, 126 }, 5)},
			{Enemy::FaceDirection::FORWARDS_RIGHT, Animation(m_pSpriteSheet, { 103, 111, 119, 127 }, 5)}
		}}
	};

	m_health.SetMaxValue(100.0f);
	m_health.SetToMaxValue();
}