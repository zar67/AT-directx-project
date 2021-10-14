#pragma once
#include "Window.h"

class Game
{
public:
	Game();
	int Run();
private:
	void Update();

	Window m_window;
};

