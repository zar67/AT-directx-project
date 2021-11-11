#pragma once

#include "Drawable.h"

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
	~UIElement() = default;

	void SetTargetCamera(Camera* camera);

	void SetOffset(Vector offset);
	virtual void Update(float deltaTime) override;

private:
	void InitialiseStatic(Graphics& graphics);

	Camera* m_camera = nullptr;
	Vector m_offset = Vector();
};