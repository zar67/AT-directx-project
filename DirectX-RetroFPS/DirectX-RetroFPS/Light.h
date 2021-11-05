#pragma once
#include "Drawable.h"

class Light : public Drawable<Light>
{
public:
	const static int MAX_SCENE_LIGHTS = 4;

	struct DiffuseData
	{
		DirectX::XMFLOAT3 Position;
		float Strength;
		alignas(16) DirectX::XMFLOAT3 Colour;
	};

	struct LightBufferData
	{
		DirectX::XMFLOAT3 AmbientColour;
		float AttenuationConstant;

		float AttenuationLinear;
		float AttenuationQuadratic;
		float paddingOne;
		float paddingTwo;

		DiffuseData DiffuseLighting[MAX_SCENE_LIGHTS];
	};
public:
	Light() = default;
	Light(Graphics & graphics);

	void SetStrength(float strength);
	void SetColour(float r, float g, float b);

	DiffuseData GetBufferData();

protected:
	void InitialiseStatic(Graphics & graphics);
	void InitialiseCollider();

	float m_strength = 1;
	DirectX::XMFLOAT3 m_colour = { 1.0f, 1.0f, 1.0f };
};