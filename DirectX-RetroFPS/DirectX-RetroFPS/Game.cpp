#include "Game.h"

Game::Game() :
	m_window(800, 600, IDS_GAMENAME, IDI_MAINICON)
{
	m_box = std::make_unique<RotatingBox>(m_window.GetGraphics(), 0.3f, 0.3f, 0.3f);
	m_box->GetTransform()->ApplyTranslation(-2.0f, 0.0f, 4.0f);

	m_light = std::make_unique<Light>(m_window.GetGraphics());
	m_light->GetTransform()->ApplyScalar(0.2f, 0.2f, 0.2f);
	m_light->GetTransform()->ApplyTranslation(12.0f, 0.0f, 12.0f);
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
	m_window.GetGraphics().GetCamera()->Update(deltaTime, 1.5f, m_window.GetInput());
	m_window.GetInput().Update();
	m_box->Update(deltaTime);
}

void Game::Render()
{
	m_window.GetGraphics().ClearBuffer(0.0f, 0.0f, 0.0f);

	m_light->Update(m_window.GetGraphics());

	// Render things...
	m_box->Draw(m_window.GetGraphics());
	m_light->Draw(m_window.GetGraphics());

	m_window.GetGraphics().RenderFrame();
}
