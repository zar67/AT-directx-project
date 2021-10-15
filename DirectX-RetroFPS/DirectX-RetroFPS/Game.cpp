/* ------------------------------------------------- */
/* Filename: Game.cpp                                */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the Game class.                                   */
/* ------------------------------------------------- */

#include "Game.h"

Game::Game() :
	m_window(1080, 720, IDS_GAMENAME, IDI_MAINICON)
{

}

int Game::Run()
{
	Init();

	while (true)
	{
		if (const auto ecode = Window::ProcessWindowsMessages())
		{
			return *ecode;
		}

		Update();
		Render();
	}

	return 0;
}

void Game::Init()
{

}

void Game::Update()
{

}

void Game::Render()
{
	m_window.GetGraphics().ClearBuffer(0.0f, 0.0f, 0.0f);

	// Render things...

	m_window.GetGraphics().RenderFrame();
}
