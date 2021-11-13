#pragma once

#include <memory>

#include "Level.h"

class LevelManager
{
public:
	LevelManager(Graphics& graphics, Player& player);
	~LevelManager() = default;

	void LoadLevel(Graphics& graphics, Player& player, int levelIndex);
	void LoadNextLevel(Graphics& graphics, Player& player);

	void DrawCurrentLevel(Graphics& graphics);
	void UpdateCurrentLevel(float deltaTime);
	void HandleCurrentLevelCollisions(Graphics& graphics);

	Level* GetCurrentLevel();

	bool IsLevelComplete(Graphics& graphics, Player& player);
	bool IsLastLevel();

private:
	int m_currentLevelIndex = 0;
	std::vector<std::unique_ptr<Level>> m_levels;
};