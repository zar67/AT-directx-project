#pragma once

#include "Drawable.h"
#include "VertexBuffer.h"
#include "SpriteSheet.h"

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

	Enemy() = default;
	Enemy(Graphics & graphics);

	virtual void Draw(Graphics& graphics) override;
	virtual void Update(float deltaTime) override;
private:
	void InitialiseStatic(Graphics & graphics);

	Graphics* m_pGraphics = nullptr;
	VertexBuffer<Vertex>* m_pVertexBuffer = nullptr;
	SpriteSheet* m_pSpriteSheet = nullptr;

	std::vector<Vertex> m_vertices = 
	{
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0, 0.2f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.03125f, 0), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.03125f, 0.2f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
	};
};