#pragma once
#include "Window.h"
#include "Timer.h"
#include "RotatingBox.h"
#include "SolidCube.h"

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

	std::unique_ptr<RotatingBox> m_box;
	std::unique_ptr<SolidCube> m_cube;
};