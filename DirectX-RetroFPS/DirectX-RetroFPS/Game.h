#pragma once

#include "Window.h"
#include "Timer.h"
#include "LevelManager.h"
#include "UIManager.h"

class Game
{
public:
	Game();
	int Run();
private:
	void Init();
	void Update(float deltaTime);
	void HandleInput();
	void Render();

	Window m_window;
	Player m_player;
	LevelManager m_levelManager;
	UIManager m_UIManager;
	Timer m_gameTimer;

	bool m_isPaused = false;
};