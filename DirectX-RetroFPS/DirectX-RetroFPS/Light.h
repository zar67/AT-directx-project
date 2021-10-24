#pragma once
#include "Drawable.h"
#include "PixelConstantBuffer.h"

class Light : public Drawable<Light>
{
public:
	Light() = default;
	Light(Graphics & graphics);

	virtual void Update(Graphics & graphics);

	void SetStrength(float strength);
	void SetColour(float r, float g, float b);
protected:
	struct BufferData
	{
		DirectX::XMFLOAT3 Colour;
		float Strength;
		DirectX::XMFLOAT3 Position;
		float Padding;
	};
protected:
	void InitialiseStatic(Graphics & graphics);

	PixelConstantBuffer<BufferData> m_constantBuffer;
	DirectX::XMFLOAT3 m_lightColour = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	float m_lightStrength = 1.0f;
};