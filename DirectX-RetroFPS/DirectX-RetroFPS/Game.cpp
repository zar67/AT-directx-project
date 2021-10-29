#include "Game.h"

Game::Game() :
	m_window(800, 600, IDS_GAMENAME, IDI_MAINICON),
	m_levelManager(m_window.GetGraphics())
{
	m_light = std::make_unique<Light>(m_window.GetGraphics());
	m_light->GetTransform()->ApplyScalar(0.5f, 0.5f, 0.5f);
	m_light->GetTransform()->ApplyTranslation(4.0f, 0.0f, 2.0f);
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
	bool wasPaused = m_isPaused;
	if (m_window.GetInput().GetKeyboard().GetKeyState(VK_ESCAPE) == Keyboard::KeyState::PRESSED)
	{
		m_isPaused = !m_isPaused;
	}

	if (m_isPaused)
	{
		m_window.ShowCursor();
	}
	else
	{
		if (wasPaused)
		{
			m_window.HideCursor();
		}

		m_window.GetGraphics().GetCamera()->Update(deltaTime, m_window.GetInput(), m_window.GetWidth(), m_window.GetHeight());
		
	}
	
	m_window.GetInput().Update();
}

void Game::Render()
{
	m_window.GetGraphics().ClearBuffer(0.0f, 0.0f, 0.0f);

	m_light->Bind(m_window.GetGraphics());

	m_light->Draw(m_window.GetGraphics());
	m_levelManager.DrawCurrentLevel(m_window.GetGraphics());

	m_window.GetGraphics().RenderFrame();
}
