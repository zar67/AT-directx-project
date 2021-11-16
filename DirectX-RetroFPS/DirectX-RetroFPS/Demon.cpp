#include "Demon.h"
#include "CollisionUtilities.h"

Demon::Demon(Graphics& graphics, Player& player) : Enemy(graphics, player)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, "Assets\\Characters\\doom_demon.png", 32, 5);
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
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 64, 72, 80, 88 }, 5)},
			{Enemy::FaceDirection::FORWARDS_LEFT, Animation(m_pSpriteSheet, { 65, 73, 81, 89 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 66, 74, 82, 90 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_LEFT, Animation(m_pSpriteSheet, { 67, 75, 83, 91 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 68, 76, 84, 92 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_RIGHT, Animation(m_pSpriteSheet, { 69, 77, 85, 93 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 70, 78, 86, 94 }, 5)},
			{Enemy::FaceDirection::FORWARDS_RIGHT, Animation(m_pSpriteSheet, { 71, 79, 87, 95 }, 5)}
		}},
		{Enemy::EnemyState::HURT, {
			{Enemy::FaceDirection::FORWARDS, Animation(m_pSpriteSheet, { 32, 40, 48, 56 }, 5)},
			{Enemy::FaceDirection::FORWARDS_LEFT, Animation(m_pSpriteSheet, { 33, 41, 49, 57 }, 5)},
			{Enemy::FaceDirection::LEFT, Animation(m_pSpriteSheet, { 34, 42, 50, 58 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_LEFT, Animation(m_pSpriteSheet, { 35, 43, 51, 59 }, 5)},
			{Enemy::FaceDirection::BACKWARDS, Animation(m_pSpriteSheet, { 36, 44, 52, 60 }, 5)},
			{Enemy::FaceDirection::BACKWARDS_RIGHT, Animation(m_pSpriteSheet, { 37, 45, 53, 61 }, 5)},
			{Enemy::FaceDirection::RIGHT, Animation(m_pSpriteSheet, { 38, 46, 54, 62 }, 5)},
			{Enemy::FaceDirection::FORWARDS_RIGHT, Animation(m_pSpriteSheet, { 39, 47, 55, 63 }, 5)}
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

	if (m_seesPlayer)
	{
		if (m_shootTimer + 0.75f >= m_shootDelay && m_currentState != EnemyState::ATTACKING)
		{
			m_currentState = EnemyState::ATTACKING;
			m_animationMap[m_currentState][m_currentDirection].Reset();
		}

		if (m_shootTimer >= m_shootDelay)
		{
			m_shootTimer = 0;
			Vector starterPosition = m_transform.Position + m_transform.TransformPoint(Vector(-0.5f, 1.0f, 0.0f));

			std::unique_ptr<Fireball> newFireball = std::make_unique<Fireball>(
				m_pGraphics,
				m_pPlayer,
				10.0f
				);

			newFireball->GetTransform().ApplyScalar(0.2f, 0.2f, 0.2f);
			newFireball->SetStartPosition(starterPosition);
			newFireball->SetDirection(m_pPlayer->GetTransform().Position - starterPosition);

			m_fireballs.push_back(std::move(newFireball));
		}
	}
	
	if (m_currentState == EnemyState::ATTACKING)
	{
		if (m_animationMap[m_currentState][m_currentDirection].Completed())
		{
			m_currentState = EnemyState::IDLE;
			m_animationMap[m_currentState][m_currentDirection].Reset();
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