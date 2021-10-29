#pragma once
#include "Window.h"
#include "Timer.h"
#include "Light.h"
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
	void Render();

	Window m_window;
	LevelManager m_levelManager;
	Timer m_gameTimer;

	std::unique_ptr<Light> m_light;

	bool m_isPaused = false;
};