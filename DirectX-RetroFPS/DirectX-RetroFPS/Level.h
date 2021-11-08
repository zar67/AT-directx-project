#pragma once

#include <memory>

#include "Graphics.h"
#include "DrawableBase.h"
#include "PixelConstantBuffer.h"
#include "Light.h"
#include "Enemy.h"

class Level
{
public:
	Level(Graphics& graphics, std::string filename);
	~Level() = default;

	void Initialise(Graphics& graphics);
	void Draw(Graphics& graphics);
	void Update(float deltaTime);

	int GetGeometryCount();
	DrawableBase* GetGeometryAtIndex(int index);

	const float UNIT_SIZE = 1.0f;

	const DirectX::XMFLOAT3 AMBIENT_COLOUR = {0.14f, 0.14f, 0.14f};

	const float ATTENUATION_CONSTANT = 1.0f;
	const float ATTENUATION_LINEAR = 0.045f;
	const float ATTENUATION_QUADRATIC = 0.0075f;

private:
	void GenerateDataFromFile(Graphics& graphics, std::string filename);
	void ParseLevelDataCharacter(Graphics& graphics, char character, float xPosition, float yPosition, float zPosition);

	void BindLighting(Graphics& graphics);

	float m_width;
	float m_depth;

	Vector m_startingPosition;
	float m_startLookRotation;

	std::vector<std::unique_ptr<DrawableBase>> m_geometry;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Light>> m_lights;

	PixelConstantBuffer<Light::LightBufferData> m_lightConstantBuffer;
};