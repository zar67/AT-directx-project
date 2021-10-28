#include "LevelManager.h"
#include <filesystem>

LevelManager::LevelManager()
{
	std::string directoryName = "Assets\\LevelData";

	for (const auto& entry : std::filesystem::directory_iterator(directoryName))
	{
		m_levels.push_back(Level(entry.path().string()));
	}
}

void LevelManager::LoadLevel(Graphics& graphics, int levelIndex)
{
	m_currentLevelIndex = levelIndex;
	m_levels[levelIndex].Initialise(graphics);
}

void LevelManager::LoadNextLevel(Graphics& graphics)
{
	m_currentLevelIndex++;
	m_levels[m_currentLevelIndex].Initialise(graphics);
}

Level LevelManager::GetCurrentLevel()
{
	return m_levels[m_currentLevelIndex];
}