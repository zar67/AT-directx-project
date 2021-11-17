#pragma once

#include <map>

#include "Drawable.h"
#include "VertexBuffer.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Player.h"
#include "Stat.h"

class Enemy : public Drawable<Enemy>
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 TextureCoords;
		DirectX::XMFLOAT3 Colour;
	};

	enum class FaceDirection {
		FORWARDS,
		FORWARDS_LEFT,
		LEFT,
		BACKWARDS_LEFT,
		BACKWARDS,
		BACKWARDS_RIGHT,
		RIGHT,
		FORWARDS_RIGHT
	};

	enum class EnemyState {
		IDLE,
		MOVING,
		ATTACKING,
		HURT,
		DEATH
	};

public:
	Enemy(Graphics & graphics, Player& player);

	void Draw(Graphics& graphics) override;
	virtual void Update(float deltaTime) override;

	virtual void OnShot(DrawableBase* shooter, float damage, Vector shotContactPosition) override;
	virtual void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other);

	virtual void PlaySightSound() {};
	virtual void PlayAttackSound() {};
	virtual void PlayInjuredSound() {};
	virtual void PlayDeathSound() {};

	void ChangeState(EnemyState state);
	void ChangeDirection(FaceDirection direction);

protected:
	std::vector<TextureCoordinate> m_textureCoords = {
		{TextureCoordinate::Position::BOTTOM_LEFT, DirectX::XMFLOAT2(0.0f, 0.0f)},
		{TextureCoordinate::Position::TOP_LEFT, DirectX::XMFLOAT2(0.0f, 0.0f)},
		{TextureCoordinate::Position::TOP_RIGHT, DirectX::XMFLOAT2(0.0f, 0.0f)},
		{TextureCoordinate::Position::BOTTOM_RIGHT, DirectX::XMFLOAT2(0.0f, 0.0f)}
	};

	std::vector<Vertex> m_vertices = {
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
	};

	std::map<EnemyState, std::map<FaceDirection, Animation>> m_animationMap;

	Graphics* m_pGraphics = nullptr;
	Player* m_pPlayer = nullptr;

	Stat m_health;
	float m_movementSpeed = 0;

	bool m_seesPlayer = false;
	float m_playerLookDistance = 6.0f;

	VertexBuffer<Vertex>* m_pVertexBuffer = nullptr;
	SpriteSheet* m_pSpriteSheet = nullptr;

	FaceDirection m_currentDirection = FaceDirection::FORWARDS;
	EnemyState m_currentState = EnemyState::IDLE;

	Vector m_lookVector = Vector(0.0f, 0.0f, -1.0f);

private:
	void InitialiseStatic(Graphics & graphics);
	void InitialiseCollider();

	void RotateToPlayer();
	void UpdateFacingDirection();
	void MoveToPlayer(float deltaTime);

	float m_hurtTimer = 0;
	float m_hurtDelay = 0.15f;
};