#include "Game.h"

#include "CollisionUtilities.h"

Game::Game() :
	m_window(800, 600, IDS_GAMENAME, IDI_MAINICON),
	m_player(m_window.GetInput(), m_window.GetWidth(), m_window.GetHeight(), 6.0f, 3.0f, DirectX::XMFLOAT2(50, 50)),
	m_levelManager(m_window.GetGraphics(), m_player),
	m_UIManager(m_window.GetGraphics())
{
	m_window.GetGraphics().GetCamera()->SetTargetTransform(m_player.GetTransform());
}

int Game::Run()
{
	Init();

	while (true)
	{
		float deltaTime = m_gameTimer.Mark();

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
	HandleInput();

	m_UIManager.Update(deltaTime);
	switch (m_UIManager.GetCurrentScreenID())
	{
		case UIManager::ScreenID::MAIN_MENU:
		{
			m_UIManager.GoToScreen(UIManager::ScreenID::GAME_HUD);
			break;
		}
		case UIManager::ScreenID::GAME_HUD:
		{
			if (!m_isPaused)
			{
				m_player.Update(deltaTime);

				m_levelManager.UpdateCurrentLevel(deltaTime);
				m_levelManager.HandleCurrentLevelCollisions(m_window.GetGraphics());

				m_window.GetGraphics().GetCamera()->UpdateViewMatrix();
			}
			break;
		}
		case UIManager::ScreenID::GAME_OVER:
		{
			break;
		}
	}

	m_window.GetInput().UpdateStates();
}

void Game::HandleInput()
{
	KeyboardEvent keyboardEvent = m_window.GetInput().GetKeyboard().ReadKey();
	while (keyboardEvent.GetType() != KeyboardEvent::EventType::INVALID)
	{
		if (keyboardEvent.GetKeyCode() == VK_ESCAPE && keyboardEvent.GetType() == KeyboardEvent::EventType::PRESS)
		{
			if (m_isPaused)
			{
				m_window.HideCursor();
			}
			else
			{
				m_window.ShowCursor();
			}

			m_isPaused = !m_isPaused;
		}

		keyboardEvent = m_window.GetInput().GetKeyboard().ReadKey();
	}

	char characterEvent = m_window.GetInput().GetKeyboard().ReadChar();
	while (characterEvent != 0u)
	{
		// Handle character pressed
		characterEvent = m_window.GetInput().GetKeyboard().ReadChar();
	}

	MouseEvent mouseEvent = m_window.GetInput().GetMouse().Read();
	while (mouseEvent.GetType() != MouseEvent::EventType::INVALID)
	{
		// Handle Mouse Event
		mouseEvent = m_window.GetInput().GetMouse().Read();
	}
}

void Game::Render()
{
	m_window.GetGraphics().ClearBuffer(0.0f, 0.0f, 0.0f);

	m_UIManager.Draw(m_window.GetGraphics());
	m_levelManager.DrawCurrentLevel(m_window.GetGraphics());

	m_window.GetGraphics().RenderFrame();
}