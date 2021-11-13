#pragma once

#include "Drawable.h"
#include "VertexBuffer.h"
#include "TextureCoordinate.h"

class UIElement : public Drawable<UIElement>
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
	UIElement(Graphics& graphics);
	virtual ~UIElement() = default;

	void SetTargetCamera(Camera* camera);

	void SetOffset(Vector offset);
	virtual void Update(float deltaTime) override;

protected:
	void InitialiseStatic(Graphics& graphics);

	std::vector<TextureCoordinate> m_textureCoords = {
		{TextureCoordinate::Position::BOTTOM_LEFT, DirectX::XMFLOAT2(0.0f, 1.0f)},
		{TextureCoordinate::Position::TOP_LEFT, DirectX::XMFLOAT2(0.0f, 0.0f)},
		{TextureCoordinate::Position::TOP_RIGHT, DirectX::XMFLOAT2(1.0f, 0.0f)},
		{TextureCoordinate::Position::BOTTOM_RIGHT, DirectX::XMFLOAT2(1.0f, 1.0f)}
	};

	std::vector<Vertex> m_vertices = {
		{DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f), DirectX::XMFLOAT3(0, 0, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f), DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)},
	};

	VertexBuffer<Vertex>* m_pVertexBuffer = nullptr;
	Camera* m_camera = nullptr;
	Vector m_offset = Vector();
};