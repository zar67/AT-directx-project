#include "LevelManager.h"
#include <filesystem>

LevelManager::LevelManager(Graphics& graphics)
{
	std::string directoryName = "Assets\\LevelData";

	for (const auto& entry : std::filesystem::directory_iterator(directoryName))
	{
		m_levels.push_back(std::make_unique<Level>(graphics, entry.path().string()));
	}
}

void LevelManager::LoadLevel(Graphics& graphics, int levelIndex)
{
	m_currentLevelIndex = levelIndex;
	m_levels[levelIndex]->Initialise(graphics);
}

void LevelManager::LoadNextLevel(Graphics& graphics)
{
	m_currentLevelIndex++;
	m_levels[m_currentLevelIndex]->Initialise(graphics);
}

void LevelManager::DrawCurrentLevel(Graphics& graphics)
{
	m_levels[m_currentLevelIndex]->Draw(graphics);
}