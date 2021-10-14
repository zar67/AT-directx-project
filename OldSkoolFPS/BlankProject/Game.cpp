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
	m_window.GetGraphics().ClearBuffer(0.92f, 0.86f, 0.32f);
	m_window.GetGraphics().EndFrame();
}
