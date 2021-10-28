#include "Game.h"

Game::Game() :
	m_window(800, 600, IDS_GAMENAME, IDI_MAINICON),
	m_levelManager(m_window.GetGraphics())
{

}

int Game::Run()
{
	Init();

	while (true)
	{
		float deltaTime = m_timer.Mark();

		if (const auto ecode = Window::ProcessWindowsMessages())
		{
			return *ecode;
		}

		Update(deltaTime);
		Render();
	}

	return 0;
}

void Game::Init()
{
	m_levelManager.LoadLevel(m_window.GetGraphics(), 0);
}

void Game::Update(float deltaTime)
{
	m_window.GetGraphics().GetCamera()->Update(deltaTime, 1.5f, m_window.GetInput());
	m_window.GetInput().Update();
}

void Game::Render()
{
	m_window.GetGraphics().ClearBuffer(0.0f, 0.0f, 0.0f);

	m_levelManager.DrawCurrentLevel(m_window.GetGraphics());

	m_window.GetGraphics().RenderFrame();
}
