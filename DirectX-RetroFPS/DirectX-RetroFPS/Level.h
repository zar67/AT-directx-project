#pragma once
#include "Graphics.h"
#include "DrawableBase.h"

class Level
{
public:
	Level(Graphics& graphics, std::string filename);
	~Level() = default;

	void Initialise(Graphics& graphics);
	void Draw(Graphics& graphics);

private:
	void GenerateDataFromFile(Graphics& graphics, std::string filename);
	void ParseLevelDataCharacter(Graphics& graphics, char character, int xPosition, int yPosition, int zPosition);

	float m_width;
	float m_height;

	DirectX::XMFLOAT3 m_startingPosition;
	float m_zLookRotation;

	std::vector<std::unique_ptr<DrawableBase>> m_geometry;
};