#pragma once
#include "Window.h"
#include "Timer.h"
#include "LevelManager.h"

class Game
{
public:
	Game();
	int Run();
private:
	void Init();
	void Update(float deltaTime);
	void HandleInput();
	void HandleCollision();
	void Render();

	Window m_window;
	LevelManager m_levelManager;
	Timer m_gameTimer;

	bool m_isPaused = false;
};