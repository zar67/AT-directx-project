#define NOMINMAX

#include <fstream>
#include <math.h>
#include <iostream>

#include "Level.h"
#include "TexturedCube.h"
#include "Demon.h"
#include "Zombie.h"
#include "DemonPuppy.h"

Level::Level(Graphics& graphics, Player& player, std::string filename) :
	m_lightConstantBuffer(graphics)
{
	m_pPlayer = &player;

	m_startingPosition = Vector(0.0f, 0.0f, 0.0f);
	m_startLookRotation = 0;

	GenerateDataFromFile(graphics, filename);
}

void Level::Initialise(Graphics& graphics)
{
	m_pPlayer->GetTransform().Position.Set(m_startingPosition.X, m_startingPosition.Y, m_startingPosition.Z);
	m_pPlayer->LockYPosition(m_startingPosition.Y);
	m_pPlayer->GetTransform().Rotation.Set(0.0f, m_startLookRotation, 0.0f);
}

void Level::Draw(Graphics& graphics)
{
	BindLighting(graphics);

	for (int i = 0; i < m_lights.size(); i++)
	{
		if (m_lights[i]->IsActive())
		{
			m_lights[i]->Draw(graphics);
		}
	}

	for (int i = 0; i < m_geometry.size(); i++)
	{
		if (m_geometry[i]->IsActive())
		{
			m_geometry[i]->Draw(graphics);
		}
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->IsActive())
		{
			m_enemies[i]->Draw(graphics);
		}
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
		if (m_lights[i]->IsActive())
		{
			m_lights[i]->Update(deltaTime);
		}
	}

	for (int i = 0; i < m_geometry.size(); i++)
	{
		if (m_geometry[i]->IsActive())
		{
			m_geometry[i]->Update(deltaTime);
		}
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->IsActive())
		{
			m_enemies[i]->Update(deltaTime);
		}
	}
}

void Level::HandleCollisions(Graphics& graphics)
{
	for (auto& geometry : m_geometry)
	{
		DrawableBase* drawableA = geometry.get();

		if (!drawableA->IsActive())
		{
			continue;
		}

		if (CollisionUtilities::IsCollisionPossible(drawableA->GetCollider(), m_pPlayer->GetCollider()))
		{
			CollisionUtilities::ColliderCollision collision = CollisionUtilities::IsColliding(drawableA->GetCollider(), m_pPlayer->GetCollider());
			if (collision.IsColliding)
			{
				CollisionUtilities::ResolveCollision(collision);
				drawableA->OnCollision(collision);
				m_pPlayer->OnCollision(collision);
			}
		}

		if (m_pPlayer->GetShooter().GetShootRay().IsValid() &&
			CollisionUtilities::IsCollisionPossible(m_pPlayer->GetShooter().GetShootRay(), drawableA->GetCollider()))
		{
			CollisionUtilities::RayCollision collision = CollisionUtilities::IsColliding(m_pPlayer->GetShooter().GetShootRay(), drawableA->GetCollider());
			if (collision.IsColliding)
			{
				m_pPlayer->GetShooter().RegisterCollision(collision, drawableA);
			}
		}

		for (auto& enemy : m_enemies)
		{
			DrawableBase* drawableB = enemy.get();

			if (!drawableB->IsActive())
			{
				continue;
			}

			if (CollisionUtilities::IsCollisionPossible(drawableA->GetCollider(), drawableB->GetCollider()))
			{
				CollisionUtilities::ColliderCollision collision = CollisionUtilities::IsColliding(drawableA->GetCollider(), drawableB->GetCollider());
				if (collision.IsColliding)
				{
					CollisionUtilities::ResolveCollision(collision);
					drawableA->OnCollision(collision);
					drawableB->OnCollision(collision);
				}
			}
		}
	}

	for (auto& enemy : m_enemies)
	{
		DrawableBase* drawableA = enemy.get();

		if (!drawableA->IsActive())
		{
			continue;
		}

		if (CollisionUtilities::IsCollisionPossible(drawableA->GetCollider(), m_pPlayer->GetCollider()))
		{
			CollisionUtilities::ColliderCollision collision = CollisionUtilities::IsColliding(drawableA->GetCollider(), m_pPlayer->GetCollider());
			if (collision.IsColliding)
			{
				CollisionUtilities::ResolveCollision(collision);
				drawableA->OnCollision(collision);
				m_pPlayer->OnCollision(collision);
			}
		}

		if (m_pPlayer->GetShooter().GetShootRay().IsValid() &&
			CollisionUtilities::IsCollisionPossible(m_pPlayer->GetShooter().GetShootRay(), drawableA->GetCollider()))
		{
			CollisionUtilities::RayCollision collision = CollisionUtilities::IsColliding(m_pPlayer->GetShooter().GetShootRay(), drawableA->GetCollider());
			if (collision.IsColliding)
			{
				m_pPlayer->GetShooter().RegisterCollision(collision, drawableA);
			}
		}
	}

	m_pPlayer->GetShooter().HandleHit();
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
					float radians = DirectX::XMConvertToRadians(degrees);
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
			std::vector<std::string> wallTiles = {
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures0.png",
				"Assets\\Environment\\walltextures2.png",
				"Assets\\Environment\\walltextures3.png",
				"Assets\\Environment\\walltextures4.png",
				"Assets\\Environment\\walltextures9.png",
				"Assets\\Environment\\walltextures10.png",
			};

			float textureIndex = rand() % wallTiles.size();

			std::unique_ptr<TexturedCube> pCube = std::make_unique<TexturedCube>(graphics, wallTiles[textureIndex]);
			pCube->GetTransform().ApplyTranslation(xPosition, yPosition, zPosition);
			pCube->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
			m_geometry.emplace_back(std::move(pCube));
			break;
		}
		case '+': // Floor / Ceiling
		{
			std::unique_ptr<TexturedCube> pCube = std::make_unique<TexturedCube>(graphics, "Assets\\Environment\\floortile3.png");
			pCube->GetTransform().ApplyTranslation(xPosition, yPosition, zPosition);
			pCube->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
			m_geometry.emplace_back(std::move(pCube));
			break;
		}
		case 'L': // Light
		{
			std::unique_ptr<Light> pLight = std::make_unique<Light>(graphics, "Assets\\Environment\\light.png");
			pLight->GetTransform().ApplyTranslation(xPosition, yPosition, zPosition);
			pLight->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE, UNIT_SIZE);
			pLight->GetCollider().SetStatic(true);
			pLight->SetStrength(0.5f);
			m_lights.emplace_back(std::move(pLight));
			break;
		}
		case 'P': // Level Start Position
		{
			m_startingPosition.Set(xPosition, yPosition + (UNIT_SIZE * 1.5f), zPosition);
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
		case 'M': // Demon
		{
			std::unique_ptr<Demon> pDemon = std::make_unique<Demon>(graphics, *m_pPlayer);
			pDemon->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE, zPosition);
			pDemon->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE * 2, UNIT_SIZE);
			m_enemies.emplace_back(std::move(pDemon));
			break; 
		}
		case 'Z': // Zombie
		{
			std::unique_ptr<Zombie> pZombie = std::make_unique<Zombie>(graphics, *m_pPlayer);
			pZombie->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE, zPosition);
			pZombie->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE * 2, UNIT_SIZE);
			m_enemies.emplace_back(std::move(pZombie));
			break;
		}
		case 'D': // Demon Puppy
		{
			std::unique_ptr<DemonPuppy> pPuppy = std::make_unique<DemonPuppy>(graphics, *m_pPlayer);
			pPuppy->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE, zPosition);
			pPuppy->GetTransform().ApplyScalar(UNIT_SIZE, UNIT_SIZE * 2, UNIT_SIZE);
			m_enemies.emplace_back(std::move(pPuppy));
			break;
		}
		case 'H': // Health Pickup
		{
			break;
		}
		case 'A': // Armour Pickup
		{
			break;
		}
		case 'B': // Bullet Pickup
		{
			break;
		}
		case 'N': // Directional Indicator - North
		{
			break;
		}
		case 'E': // Directional Indicator - East
		{
			break;
		}
		case 'S': // Directional Indicator - South
		{
			break;
		}
		case 'W': // Directional Indicator - West
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

	Vector cameraPosition = m_pPlayer->GetTransform().Position;

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