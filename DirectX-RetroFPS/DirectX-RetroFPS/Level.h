#pragma once

#include <memory>

#include "Graphics.h"
#include "DrawableBase.h"
#include "Light.h"

class Level
{
public:
	Level(Graphics& graphics, std::string filename);
	~Level() = default;

	void Initialise(Graphics& graphics);
	void Draw(Graphics& graphics);

	const float UNIT_SIZE = 1.0f;

private:
	void GenerateDataFromFile(Graphics& graphics, std::string filename);
	void ParseLevelDataCharacter(Graphics& graphics, char character, float xPosition, float yPosition, float zPosition);
	void DrawLights(Graphics& graphics);

	float m_width;
	float m_depth;

	DirectX::XMFLOAT3 m_startingPosition;
	float m_startLookRotation;

	std::vector<std::unique_ptr<DrawableBase>> m_geometry;
	std::vector<std::unique_ptr<Light>> m_lights;
};