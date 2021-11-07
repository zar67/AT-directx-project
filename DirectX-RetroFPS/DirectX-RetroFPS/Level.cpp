#define NOMINMAX

#include <fstream>
#include <math.h>

#include "Level.h"
#include "TexturedCube.h"

Level::Level(Graphics& graphics, std::string filename) :
	m_lightConstantBuffer(graphics)
{
	m_startingPosition = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_startLookRotation = 0;

	GenerateDataFromFile(graphics, filename);
}

void Level::Initialise(Graphics& graphics)
{
	graphics.GetCamera()->SetPosition(m_startingPosition.x, m_startingPosition.y, m_startingPosition.z);
	graphics.GetCamera()->LockYPosition(m_startingPosition.y);
	graphics.GetCamera()->SetRotation(0.0f, m_startLookRotation, 0.0f);
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
}

int Level::GetGeometryCount()
{
	return m_geometry.size();
}

DrawableBase* Level::GetGeometryAtIndex(int index)
{
	return m_geometry[index].get();
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
					float radians = degrees * (3.14f / 180);
					m_startLookRotation =  radians;

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
			std::unique_ptr<TexturedCube> pCube = std::make_unique<TexturedCube>(graphics, 0.3f, 0.3f, 0.3f);
			pCube->GetTransform().ApplyTranslation(xPosition, yPosition, zPosition);
			pCube->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
			pCube->GetCollider().SetStatic(true);
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
			m_startingPosition = DirectX::XMFLOAT3(xPosition, yPosition + (UNIT_SIZE * 1.5f), zPosition);
			break;
		}
		case 'E': // Enemy
		{
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

	DirectX::XMFLOAT3 cameraPosition = graphics.GetCamera()->GetTransform().Position;

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

			DirectX::XMFLOAT3 lightPos = m_lights[i]->GetTransform().Position;
			DirectX::XMFLOAT3 camToLight = DirectX::XMFLOAT3(
				lightPos.x - cameraPosition.x,
				lightPos.y - cameraPosition.y,
				lightPos.z - cameraPosition.z
			);

			float distSquared = pow(camToLight.x, 2) + pow(camToLight.y, 2) + pow(camToLight.z, 2);

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