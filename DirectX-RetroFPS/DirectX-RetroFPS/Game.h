#pragma once
#include "Window.h"
#include "Timer.h"
#include "RotatingBox.h"
#include "Light.h"
#include "SolidColourBox.h"
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

	LevelManager m_levelManager;
};