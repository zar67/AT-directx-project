#pragma once
#include "Drawable.h"
#include "PixelConstantBuffer.h"

class Light : public Drawable<Light>
{
public:
	Light(Graphics & graphics);

	virtual void Bind(Graphics & graphics);

	void SetStrength(float strength);
	void SetColour(float r, float g, float b);
protected:
	struct BufferData
	{
		DirectX::XMFLOAT3 Position;
		float Strength;
		DirectX::XMFLOAT3 Colour;
		float AttenuationConstant;
		DirectX::XMFLOAT3 AmbientColour;
		float AttenuationLinear;
		alignas(16) float AttenuationQuadratic;
	};
protected:
	void InitialiseStatic(Graphics & graphics);
	void InitialiseCollider();

	BufferData m_bufferData;
	PixelConstantBuffer<BufferData> m_constantBuffer;
};