#include "Zombie.h"
#include "SoundManager.h"

Zombie::Zombie(Graphics& graphics, Player& player) : Enemy(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\orc.png", 6, 4);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_pSpriteSheet->SetCoordsToSpriteAt(0, m_textureCoords);
	for (int i = 0; i < 4; i++)
	{
		m_vertices[i].TextureCoords = m_textureCoords[i].Coordinate;
	}

	m_animationMap = {
		{Enemy::EnemyState::IDLE, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 3, 4 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 9, 10 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 21, 22 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 15, 16 }, 5)}
		}},
		{Enemy::EnemyState::MOVING, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 0, 1, 2 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 6, 7, 8 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 18, 19, 20 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 12, 13, 14 }, 5)}
		}},
		{Enemy::EnemyState::ATTACKING, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 2 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 8 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 20 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 14 }, 5)}
		}},
		{Enemy::EnemyState::HURT, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 5 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 11 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 23 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 17 }, 5)}
		}},
		{Enemy::EnemyState::DEATH, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 5 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 11 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 23 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 17 }, 5)}
		}}
	};

	m_health.SetMaxValue(100.0f);
	m_health.SetToMaxValue();

	m_movementSpeed = 2.5f;
}

void Zombie::PlaySightSound()
{
	SoundManager::GetInstance().Play(SoundType::ZOMBIE_SIGHT);
}

void Zombie::PlayAttackSound()
{
	SoundManager::GetInstance().Play(SoundType::ZOMBIE_ATTACK);
}

void Zombie::PlayInjuredSound()
{
	SoundManager::GetInstance().Play(SoundType::ZOMBIE_INJURED);
}

void Zombie::PlayDeathSound()
{
	SoundManager::GetInstance().Play(SoundType::ZOMBIE_DEATH);
}
