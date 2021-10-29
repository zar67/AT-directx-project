#pragma once
#include "Level.h"

class LevelManager
{
public:
	LevelManager(Graphics& graphics);
	~LevelManager() = default;

	void LoadLevel(Graphics& graphics, int levelIndex);
	void LoadNextLevel(Graphics& graphics);
	void DrawCurrentLevel(Graphics& graphics);

private:
	int m_currentLevelIndex = 0;
	std::vector<std::unique_ptr<Level>> m_levels;
};