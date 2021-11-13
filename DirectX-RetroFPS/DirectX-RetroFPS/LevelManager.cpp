#include <filesystem>

#include "LevelManager.h"

LevelManager::LevelManager(Graphics& graphics, Player& player)
{
	std::string directoryName = "Assets\\LevelData";

	for (const auto& entry : std::filesystem::directory_iterator(directoryName))
	{
		m_levels.push_back(std::make_unique<Level>(graphics, player, entry.path().string()));
	}
}

void LevelManager::LoadLevel(Graphics& graphics, int levelIndex)
{
	m_currentLevelIndex = levelIndex;
	m_levels[levelIndex]->Initialise(graphics);
}

void LevelManager::LoadNextLevel(Graphics& graphics)
{
	if (m_currentLevelIndex + 1 < m_levels.size())
	{
		m_currentLevelIndex++;
		m_levels[m_currentLevelIndex]->Initialise(graphics);
	}
}

void LevelManager::DrawCurrentLevel(Graphics& graphics)
{
	m_levels[m_currentLevelIndex]->Draw(graphics);
}

Level* LevelManager::GetCurrentLevel()
{
	return m_levels[m_currentLevelIndex].get();
}

bool LevelManager::IsLevelComplete(Graphics& graphics, Player& player)
{
	return m_levels[m_currentLevelIndex]->IsLevelComplete(player);
}

bool LevelManager::IsLastLevel()
{
	return m_currentLevelIndex + 1 >= m_levels.size();
}

void LevelManager::ResetLevel(Graphics& graphics)
{
	m_levels[m_currentLevelIndex]->Initialise(graphics);
}

void LevelManager::UpdateCurrentLevel(float deltaTime)
{
	m_levels[m_currentLevelIndex]->Update(deltaTime);
}

void LevelManager::HandleCurrentLevelCollisions(Graphics& graphics)
{
	m_levels[m_currentLevelIndex]->HandleCollisions(graphics);
}