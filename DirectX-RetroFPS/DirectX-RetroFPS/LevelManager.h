#pragma once
#include "Level.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager() = default;

	void LoadLevel(Graphics& graphics, int levelIndex);
	void LoadNextLevel(Graphics& graphics);
	Level GetCurrentLevel();
private:
	int m_currentLevelIndex = 0;
	std::vector<Level> m_levels;
};