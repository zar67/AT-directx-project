#pragma once

#include <memory>

#include "PixelConstantBuffer.h"
#include "Light.h"
#include "Enemy.h"
#include "Pickup.h"
#include "LevelExit.h"
#include "KeyPickup.h"

class Level
{
public:
	Level(Graphics& graphics, Player& player, std::string filename);
	~Level() = default;

	void Initialise(Graphics& graphics);
	void Draw(Graphics& graphics);
	void Update(float deltaTime);
	void HandleCollisions(Graphics& graphics);

	bool IsLevelComplete(Player& player);

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

	Player* m_pPlayer = nullptr;

	float m_width;
	float m_depth;

	Vector m_startingPosition;
	float m_startLookRotation;

	std::vector<std::unique_ptr<DrawableBase>> m_geometry;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Light>> m_lights;
	std::vector<std::unique_ptr<Pickup>> m_pickups;

	std::unique_ptr<LevelExit> m_pLevelExit;

	PixelConstantBuffer<Light::LightBufferData> m_lightConstantBuffer;
};