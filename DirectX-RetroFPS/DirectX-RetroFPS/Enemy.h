#pragma once

#include "Drawable.h"
#include "VertexBuffer.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include <map>

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
		DEATH
	};

public:
	Enemy(Graphics & graphics);

	void Draw(Graphics& graphics) override;
	virtual void Update(float deltaTime) override;

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
	VertexBuffer<Vertex>* m_pVertexBuffer = nullptr;
	SpriteSheet* m_pSpriteSheet = nullptr;

	FaceDirection m_currentDirection = FaceDirection::FORWARDS;
	EnemyState m_currentState = EnemyState::IDLE;

private:
	void InitialiseStatic(Graphics & graphics);

	void RotateToPlayer();
	void UpdateFacingDirection();

	const std::map<FaceDirection, Vector> DIRECTION_MAP = {
		{FaceDirection::FORWARDS, Vector(0.0f, 0.0f, -1.0f)},
		{FaceDirection::FORWARDS_LEFT, Vector(0.5f, 0.0f, -0.5f)},
		{FaceDirection::LEFT, Vector(1.0f, 0.0f, 0.0f)},
		{FaceDirection::BACKWARDS_LEFT, Vector(0.5f, 0.0f, 0.5f)},
		{FaceDirection::BACKWARDS, Vector(0.0f, 0.0f, 1.0f)},
		{FaceDirection::BACKWARDS_RIGHT, Vector(-0.5f, 0.0f, 0.5f)},
		{FaceDirection::RIGHT, Vector(-1.0f, 0.0f, -1.0f)},
		{FaceDirection::FORWARDS_RIGHT, Vector(-0.5f, 0.0f, -0.5f)}
	};

	Vector m_lookVector = Vector(0.0f, 0.0f, -1.0f);
};