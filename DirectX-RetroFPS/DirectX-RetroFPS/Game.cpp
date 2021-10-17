/* ------------------------------------------------- */
/* Filename: Game.cpp                                */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the Game class.                                   */
/* ------------------------------------------------- */

#include "Game.h"

Game::Game() :
	m_window(800, 600, IDS_GAMENAME, IDI_MAINICON)
{
	m_box = std::make_unique<RotatingBox>(m_window.GetGraphics(), 0, 0, 1.5f);
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

}

void Game::Update(float deltaTime)
{
	m_box->Update(deltaTime);
}

void Game::Render()
{
	m_window.GetGraphics().ClearBuffer(0.0f, 0.0f, 0.0f);

	// Render things...
	m_box->Draw(m_window.GetGraphics());

	m_window.GetGraphics().RenderFrame();
}
