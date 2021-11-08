#define NOMINMAX

#include <fstream>
#include <math.h>

#include "Level.h"
#include "TexturedCube.h"

Level::Level(Graphics& graphics, std::string filename) :
	m_lightConstantBuffer(graphics)
{
	m_startingPosition = Vector(0.0f, 0.0f, 0.0f);
	m_startLookRotation = 0;

	GenerateDataFromFile(graphics, filename);
}

void Level::Initialise(Graphics& graphics)
{
	graphics.GetCamera()->GetTransform().Position.Set(m_startingPosition.X, m_startingPosition.Y, m_startingPosition.Z);
	graphics.GetCamera()->LockYPosition(m_startingPosition.Y);
	graphics.GetCamera()->GetTransform().Rotation.Set(0.0f, m_startLookRotation, 0.0f);
}

void Level::Draw(Graphics& graphics)
{
	BindLighting(graphics);

	for (int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i]->Draw(graphics);
	}

	for (int i = 0; i < m_geometry.size(); i++)
	{
		m_geometry[i]->Draw(graphics);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Draw(graphics);
	}
}

int Level::GetGeometryCount()
{
	return m_geometry.size();
}

DrawableBase* Level::GetGeometryAtIndex(int index)
{
	return m_geometry[index].get();
}

void Level::Update(float deltaTime)
{
	for (int i = 0; i < m_lights.size(); i++)
	{
		m_lights[i]->Update(deltaTime);
	}

	for (int i = 0; i < m_geometry.size(); i++)
	{
		m_geometry[i]->Update(deltaTime);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Update(deltaTime);
	}
}

void Level::GenerateDataFromFile(Graphics& graphics, std::string filename)
{
	std::ifstream file(filename);

	if (file.is_open())
	{
		int count = 0;
		float yPosition = 0.0f;
		float zPosition = 0.0f;

		while (file)
		{
			std::string line;
			std::getline(file, line);

			if (line == "")
			{
				if (count > 3)
				{
					yPosition += UNIT_SIZE * 2;
					zPosition = m_depth * (UNIT_SIZE * 2);
				}
				continue;
			}

			switch (count)
			{
				case 0:
				{
					int index = line.find(':') + 1;
					std::string subString = line.substr(index, line.size() - 1);
					m_width = std::stoi(subString);
					break;
				}
				case 1:
				{
					int index = line.find(':') + 1;
					std::string subString = line.substr(index, line.size() - 1);
					m_depth = std::stoi(subString);
					zPosition = m_depth * (UNIT_SIZE * 2);
					break;
				}
				case 2:
				{
					int index = line.find(':') + 1;
					std::string subString = line.substr(index, line.size() - 1);

					float degrees = std::stof(subString);
					float radians = degrees * (DirectX::XM_PI / 180);
					m_startLookRotation = radians;

					yPosition += UNIT_SIZE * 2;
					break;
				}
				default:
				{
					float xPosition = 0.0f;
					for (char character : line)
					{
						ParseLevelDataCharacter(graphics, character, xPosition, yPosition, zPosition);
						xPosition += UNIT_SIZE * 2;
					}

					zPosition -= UNIT_SIZE * 2;
					break;
				}
			}

			count++;
		}
	}

	file.close();
}

void Level::ParseLevelDataCharacter(Graphics& graphics, char character, float xPosition, float yPosition, float zPosition)
{
	switch (character)
	{
		case '#': // Wall
		{
			std::unique_ptr<TexturedCube> pCube = std::make_unique<TexturedCube>(graphics);
			pCube->GetTransform().ApplyTranslation(xPosition, yPosition, zPosition);
			pCube->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
			m_geometry.emplace_back(std::move(pCube));
			break;
		}
		case 'L': // Light
		{
			std::unique_ptr<Light> pLight = std::make_unique<Light>(graphics);
			pLight->GetTransform().ApplyTranslation(xPosition, yPosition, zPosition);
			pLight->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
			pLight->GetCollider().SetStatic(true);
			m_lights.emplace_back(std::move(pLight));
			break;
		}
		case 'S': // Level Start Position
		{
			m_startingPosition.Set(xPosition, yPosition + (UNIT_SIZE * 1.5f), zPosition);
			break;
		}
		case 'E': // Enemy
		{
			std::unique_ptr<Enemy> pEnemy = std::make_unique<Enemy>(graphics);
			pEnemy->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE, zPosition);
			pEnemy->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE * 2, UNIT_SIZE);
			m_enemies.emplace_back(std::move(pEnemy));
			break;
			break;
		}
		case 'K': // Key
		{
			break;
		}
		case 'F': // Level End Position
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

void Level::BindLighting(Graphics& graphics)
{
	Light::LightBufferData lightBufferData;
	lightBufferData.AmbientColour = AMBIENT_COLOUR;
	lightBufferData.AttenuationConstant = ATTENUATION_CONSTANT;
	lightBufferData.AttenuationLinear = ATTENUATION_LINEAR;
	lightBufferData.AttenuationQuadratic = ATTENUATION_QUADRATIC;

	Vector cameraPosition = graphics.GetCamera()->GetTransform().Position;

	float excludedIndexes[Light::MAX_SCENE_LIGHTS];
	for (int i = 0; i < Light::MAX_SCENE_LIGHTS; i++)
	{
		excludedIndexes[i] = -1;
	}

	for (int l = 0; l < Light::MAX_SCENE_LIGHTS; l++)
	{
		float closestDistance = std::numeric_limits<float>::max();
		float closestIndex = 0;

		for (int i = 0; i < m_lights.size(); i++)
		{
			bool brk = false;
			for (int j = 0; j < Light::MAX_SCENE_LIGHTS; j++)
			{
				if (i == excludedIndexes[j])
				{
					brk = true;
					break;
				}
			}

			if (brk)
			{
				continue;
			}

			Vector lightPos = m_lights[i]->GetTransform().Position;
			Vector camToLight = lightPos - cameraPosition;

			float distSquared = camToLight.GetMagnitudeSquared();

			if (distSquared < closestDistance)
			{
				closestDistance = distSquared;
				closestIndex = i;
				excludedIndexes[l] = i;
			}
		}
	}

	for (int i = 0; i < Light::MAX_SCENE_LIGHTS; i++)
	{
		lightBufferData.DiffuseLighting[i] = m_lights[excludedIndexes[i]]->GetBufferData();
	}

	m_lightConstantBuffer.Update(graphics, lightBufferData);
	m_lightConstantBuffer.Bind(graphics);
}