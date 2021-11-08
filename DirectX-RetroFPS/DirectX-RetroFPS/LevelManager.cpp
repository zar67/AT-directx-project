#include <filesystem>

#include "LevelManager.h"

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

Level* LevelManager::GetCurrentLevel()
{
	return m_levels[m_currentLevelIndex].get();
}

void LevelManager::UpdateCurrentLevel(float deltaTime)
{
	m_levels[m_currentLevelIndex]->Update(deltaTime);
}

void LevelManager::HandleCurrentLevelCollisions(Graphics& graphics)
{
	m_levels[m_currentLevelIndex]->HandleCollisions(graphics);
}