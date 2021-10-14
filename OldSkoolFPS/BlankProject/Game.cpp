#include "Game.h"

Game::Game() :
	m_window(1080, 720, IDS_GAMENAME, IDI_MAINICON)
{

}

int Game::Run()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessages())
		{
			return *ecode;
		}

		Update();
	}

	return 0;
}

void Game::Update()
{

}
