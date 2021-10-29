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
	void Render();

	Window m_window;
	Timer m_timer;

	std::unique_ptr<Light> m_light;
	LevelManager m_levelManager;

	bool m_isPaused = false;
};