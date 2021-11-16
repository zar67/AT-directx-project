#pragma once

#include "Drawable.h"
#include "Player.h"
#include "TextureCoordinate.h"
#include "SpriteSheet.h"
#include "VertexBuffer.h"

class Fireball : public Drawable<Fireball>
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 TextureCoords;
		DirectX::XMFLOAT3 Colour;
	};
public:
	Fireball(Graphics* graphics, Player* player, float damage);

	void Draw(Graphics& graphics) override;
	virtual void Update(float deltaTime) override;

	virtual void OnShot(DrawableBase* shooter, float damage, Vector shotContactPosition) override;
	virtual void OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other);

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
private:
	void InitialiseStatic(Graphics& graphics);
	void InitialiseCollider();

	void RotateToPlayer();

	Graphics* m_pGraphics = nullptr;
	Player* m_pPlayer = nullptr;

	VertexBuffer<Vertex>* m_pVertexBuffer = nullptr;
	SpriteSheet* m_pSpriteSheet = nullptr;

	Vector m_direction;
	float m_damage;
	float m_movementSpeed;
};