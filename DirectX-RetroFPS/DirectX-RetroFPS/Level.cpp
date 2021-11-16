#define NOMINMAX

#include <fstream>
#include <math.h>

#include "Level.h"
#include "TexturedCube.h"
#include "Demon.h"
#include "Zombie.h"
#include "DemonPuppy.h"
#include "HealthPickup.h"
#include "ArmorPickup.h"
#include "BulletPickup.h"

Level::Level(Graphics& graphics, Player& player, std::string filename) :
	m_lightConstantBuffer(graphics)
{
	m_filename = filename;
	m_pPlayer = &player;

	m_startingPosition = Vector(0.0f, 0.0f, 0.0f);
	m_startLookRotation = 0;

	Reset(graphics, player);
}

void Level::Initialise()
{
	m_pPlayer->GetTransform().Position.Set(m_startingPosition.X, m_startingPosition.Y, m_startingPosition.Z);
	m_pPlayer->LockYPosition(m_startingPosition.Y);
	m_pPlayer->GetTransform().Rotation.Set(0.0f, m_startLookRotation, 0.0f);
}

void Level::Reset(Graphics& graphics, Player& player)
{
	m_startingPosition = Vector(0.0f, 0.0f, 0.0f);
	m_startLookRotation = 0;

	m_geometry.clear();
	m_enemies.clear();
	m_lights.clear();
	m_pickups.clear();

	m_pLevelExit = nullptr;

	GenerateDataFromFile(graphics, m_filename);
	Initialise();
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

	for (int i = 0; i < m_pickups.size(); i++)
	{
		m_pickups[i]->Draw(graphics);
	}

	m_pLevelExit->Draw(graphics);
}

bool Level::IsLevelComplete(Player& player)
{
	return player.HasKey() && m_pLevelExit->IsColliding();
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

	for (int i = 0; i < m_pickups.size(); i++)
	{
		if (m_pickups[i]->IsActive())
		{
			m_pickups[i]->Update(deltaTime);
		}
	}

	m_pLevelExit->Update(deltaTime);
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
				drawableA->OnCollision(collision, m_pPlayer);
				m_pPlayer->OnCollision(collision, drawableA);
			}
		}

		if (m_pPlayer->GetShooter().IsShooting() &&
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
					drawableA->OnCollision(collision, drawableB);
					drawableB->OnCollision(collision, drawableA);
				}
			}
		}

		if (CollisionUtilities::IsCollisionPossible(m_pPlayer->GetCollider(), m_pLevelExit->GetCollider()))
		{
			CollisionUtilities::ColliderCollision collision = CollisionUtilities::IsColliding(m_pPlayer->GetCollider(), m_pLevelExit->GetCollider());
			if (collision.IsColliding)
			{
				CollisionUtilities::ResolveCollision(collision);
				m_pPlayer->OnCollision(collision, m_pLevelExit.get());
				m_pLevelExit->OnCollision(collision, m_pPlayer);
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
				drawableA->OnCollision(collision, m_pPlayer);
				m_pPlayer->OnCollision(collision, drawableA);
			}
		}

		if (m_pPlayer->GetShooter().IsShooting() &&
			CollisionUtilities::IsCollisionPossible(m_pPlayer->GetShooter().GetShootRay(), drawableA->GetCollider()))
		{
			CollisionUtilities::RayCollision collision = CollisionUtilities::IsColliding(m_pPlayer->GetShooter().GetShootRay(), drawableA->GetCollider());
			if (collision.IsColliding)
			{
				m_pPlayer->GetShooter().RegisterCollision(collision, drawableA);
			}
		}

		Demon* pDemon = dynamic_cast<Demon*>(drawableA);
		if (pDemon != nullptr)
		{
			pDemon->HandleFireballCollisions();
		}
	}

	for (auto& pickup : m_pickups)
	{
		DrawableBase* drawable = pickup.get();

		if (!drawable->IsActive())
		{
			continue;
		}

		if (CollisionUtilities::IsCollisionPossible(drawable->GetCollider(), m_pPlayer->GetCollider()))
		{
			CollisionUtilities::ColliderCollision collision = CollisionUtilities::IsColliding(drawable->GetCollider(), m_pPlayer->GetCollider());
			if (collision.IsColliding)
			{
				drawable->OnCollision(collision, m_pPlayer);
				m_pPlayer->OnCollision(collision, drawable);
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
			std::unique_ptr<KeyPickup> keyPickup = std::make_unique<KeyPickup>(graphics, *m_pPlayer);
			keyPickup->GetTransform().ApplyTranslation(xPosition, yPosition, zPosition);
			m_pickups.push_back(std::move(keyPickup));
			break;
		}
		case 'F': // Level End Position
		{
			m_pLevelExit = std::make_unique<LevelExit>(graphics);
			m_pLevelExit->GetTransform().ApplyScalar(1.0f, 2.0f, 1.0f);
			m_pLevelExit->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE, zPosition);
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
			std::unique_ptr<HealthPickup> pHealthPickup = std::make_unique<HealthPickup>(graphics, *m_pPlayer);
			pHealthPickup->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE / 3, zPosition);
			pHealthPickup->GetTransform().ApplyScalar(UNIT_SIZE / 2, UNIT_SIZE / 2, UNIT_SIZE / 2);
			m_pickups.emplace_back(std::move(pHealthPickup));
			break;
		}
		case 'A': // Armor Pickup
		{
			std::unique_ptr<ArmorPickup> pArmorPickup = std::make_unique<ArmorPickup>(graphics, *m_pPlayer);
			pArmorPickup->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE / 3, zPosition);
			pArmorPickup->GetTransform().ApplyScalar(UNIT_SIZE / 2, UNIT_SIZE / 2, UNIT_SIZE / 2);
			m_pickups.emplace_back(std::move(pArmorPickup));
			break;
		}
		case 'B': // Bullet Pickup
		{
			int type = (rand() % 4) + 2;
			int bulletAmounts[4] = {5, 10, 5, 2};
			std::unique_ptr<BulletPickup> pBulletPickup = std::make_unique<BulletPickup>(graphics, *m_pPlayer, (WeaponType)type, bulletAmounts[type - 2]);
			pBulletPickup->GetTransform().ApplyTranslation(xPosition, yPosition + UNIT_SIZE / 3, zPosition);
			pBulletPickup->GetTransform().ApplyScalar(UNIT_SIZE / 2, UNIT_SIZE / 2, UNIT_SIZE / 2);
			m_pickups.emplace_back(std::move(pBulletPickup));
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