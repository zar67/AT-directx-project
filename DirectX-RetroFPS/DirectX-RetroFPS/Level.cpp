#include "Level.h"
#include <fstream>
#include "RotatingBox.h"

Level::Level(Graphics& graphics, std::string filename)
{
	m_startingPosition = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_zLookRotation = 0;

	GenerateDataFromFile(graphics, filename);
}

void Level::Initialise(Graphics& graphics)
{
	graphics.GetCamera()->SetPosition(m_startingPosition.x, m_startingPosition.y, m_startingPosition.z);
	graphics.GetCamera()->SetRotation(0.0f, 0.0f, m_zLookRotation);
}

void Level::Draw(Graphics& graphics)
{
	for (int i = 0; i < m_geometry.size(); i++)
	{
		m_geometry[i]->Draw(graphics);
	}
}

void Level::GenerateDataFromFile(Graphics& graphics, std::string filename)
{
	std::ifstream file(filename);

	if (file.is_open())
	{
		int count = 0;
		int yPosition = 0;
		int zPosition = 0;
		while (file)
		{
			std::string line;
			std::getline(file, line);

			if (line == "")
			{
				if (count > 3)
				{
					yPosition++;
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
					m_height = std::stoi(subString);
					break;
				}
				case 2:
				{
					int index = line.find(':') + 1;
					std::string subString = line.substr(index, line.size() - 1);
					m_height = std::stof(subString);
					break;
				}
				default:
				{
					int xPosition = 0;
					for (char character : line)
					{
						ParseLevelDataCharacter(graphics, character, xPosition, yPosition, zPosition);
						xPosition++;
					}

					zPosition++;
					break;
				}
			}

			count++;
		}
	}

	file.close();
}

void Level::ParseLevelDataCharacter(Graphics& graphics, char character, int xPosition, int yPosition, int zPosition)
{
	switch (character)
	{
		case '#': // Wall
		{
			std::unique_ptr<RotatingBox> pCube = std::make_unique<RotatingBox>(graphics, 0, 0, 0);
			pCube->GetTransform()->ApplyTranslation(xPosition, yPosition, zPosition);
			pCube->GetTransform()->ApplyScalar(0.5f, 0.5f, 0.5f);
			m_geometry.emplace_back(std::move(pCube));
			break;
		}
		case 'S': // Level Start Position
		{
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
	}
}