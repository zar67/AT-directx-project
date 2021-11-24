#include "Demon.h"
#include "CollisionUtilities.h"
#include "SoundManager.h"

Demon::Demon(Graphics& graphics, Player& player) : Enemy(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\fireball_enemy.png", 6, 4);
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

	m_health.SetMaxValue(150.0f);
	m_health.SetToMaxValue();

	m_movementSpeed = 0;
}

void Demon::Draw(Graphics& graphics)
{
	Enemy::Draw(graphics);

	for (auto& fireball : m_fireballs)
	{
		fireball->Draw(graphics);
	}
}

void Demon::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	m_shootTimer += deltaTime;

	if (m_seesPlayer && m_currentState != EnemyState::HURT)
	{
		if (m_shootTimer + 0.75f >= m_shootDelay && m_currentState != EnemyState::ATTACKING)
		{
			ChangeState(EnemyState::ATTACKING);
		}

		if (m_shootTimer >= m_shootDelay)
		{
			m_shootTimer = 0;

			std::unique_ptr<Fireball> newFireball = std::make_unique<Fireball>(
				m_pGraphics,
				m_pPlayer,
				10.0f
			);

			newFireball->GetTransform().ApplyScalar(0.2f, 0.2f, 0.2f);
			newFireball->SetStartPosition(m_transform.Position);
			newFireball->SetDirection(m_pPlayer->GetTransform().Position - m_transform.Position);

			SoundManager::GetInstance().Play(SoundType::DEMON_ATTACK);
			m_fireballs.push_back(std::move(newFireball));
		}
	}
	
	if (m_currentState == EnemyState::ATTACKING)
	{
		if (m_animationMap[m_currentState][m_currentDirection].Completed())
		{
			ChangeState(EnemyState::IDLE);
		}
	}

	for (int i = m_fireballs.size() - 1; i >= 0; i--)
	{
		if (m_fireballs[i]->IsActive())
		{
			m_fireballs[i]->Update(deltaTime);
		}
		else
		{
			m_fireballs.erase(m_fireballs.begin()+i);
		}
	}
}

void Demon::OnShot(DrawableBase* shooter, float damage, Vector shotContactPosition)
{
	Enemy::OnShot(shooter, damage, shotContactPosition);

	if (m_health.IsZero())
	{
		m_fireballs.clear();
	}
}

void Demon::HandleFireballCollisions(DrawableBase* drawable)
{
	for (auto& fireball : m_fireballs)
	{
		if (CollisionUtilities::IsCollisionPossible(drawable->GetCollider(), fireball->GetCollider()))
		{
			CollisionUtilities::ColliderCollision collision = CollisionUtilities::IsColliding(drawable->GetCollider(), fireball->GetCollider());
			if (collision.IsColliding)
			{
				fireball->OnCollision(collision, drawable);
				drawable->OnCollision(collision, fireball.get());
			}
		}
	}
}

void Demon::HandlePlayerFireballCollision()
{
	for (auto& fireball : m_fireballs)
	{
		if (CollisionUtilities::IsCollisionPossible(m_pPlayer->GetCollider(), fireball->GetCollider()))
		{
			CollisionUtilities::ColliderCollision collision = CollisionUtilities::IsColliding(m_pPlayer->GetCollider(), fireball->GetCollider());
			if (collision.IsColliding)
			{
				fireball->OnCollision(collision, m_pPlayer);
				m_pPlayer->OnCollision(collision, fireball.get());
			}
		}

		if (m_pPlayer->GetShooter().IsShooting() &&
			CollisionUtilities::IsCollisionPossible(m_pPlayer->GetShooter().GetShootRay(), fireball->GetCollider()))
		{
			CollisionUtilities::RayCollision collision = CollisionUtilities::IsColliding(m_pPlayer->GetShooter().GetShootRay(), fireball->GetCollider());
			if (collision.IsColliding)
			{
				m_pPlayer->GetShooter().RegisterCollision(collision, fireball.get());
			}
		}
	}
}

void Demon::PlaySightSound()
{
	SoundManager::GetInstance().Play(SoundType::DEMON_SIGHT);
}

void Demon::PlayAttackSound()
{
	SoundManager::GetInstance().Play(SoundType::DEMON_ATTACK);
}

void Demon::PlayInjuredSound()
{
	SoundManager::GetInstance().Play(SoundType::DEMON_INJURED);
}

void Demon::PlayDeathSound()
{
	SoundManager::GetInstance().Play(SoundType::DEMON_DEATH);
}