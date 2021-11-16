#include "Game.h"

#include "CollisionUtilities.h"
#include "GameHUDScreen.h"

Game::Game() :
	m_player(m_window.GetInput(), WINDOW_WIDTH, WINDOW_HEIGHT, 6.0f, 3.0f, DirectX::XMFLOAT2(50, 50)),
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
	m_levelManager.LoadLevel(m_window.GetGraphics(), m_player, 0);
}

void Game::Update(float deltaTime)
{
	HandleInput();

	if (m_UIManager.GetCurrentScreenID() == ScreenType::GAME_HUD)
	{
		if (!m_isPaused)
		{
			m_player.Update(deltaTime);

			((GameHUDScreen*)m_UIManager.GetCurrentScreen())->UpdateHUD(m_player);

			m_levelManager.UpdateCurrentLevel(deltaTime);
			m_levelManager.HandleCurrentLevelCollisions(m_window.GetGraphics());
			
			if (m_levelManager.IsLevelComplete(m_window.GetGraphics(), m_player))
			{
				if (m_levelManager.IsLastLevel())
				{
					m_UIManager.GoToScreen(ScreenType::MAIN_MENU);
					m_levelManager.LoadLevel(m_window.GetGraphics(), m_player, 0);
				}
				else
				{
					m_levelManager.LoadNextLevel(m_window.GetGraphics(), m_player);
				}
			}

			if (m_player.GetHealth().IsZero())
			{
				m_UIManager.GoToScreen(ScreenType::GAME_OVER);
				m_levelManager.LoadLevel(m_window.GetGraphics(), m_player, 0);
				m_player.Reset();
			}
		}
	}

	m_window.GetGraphics().GetCamera()->UpdateViewMatrix();

	m_UIManager.Update(deltaTime);

	m_window.GetInput().UpdateStates();
}

void Game::HandleInput()
{
	m_UIManager.HandleInput(m_window.GetInput());

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
	m_window.GetGraphics().ClearRenderTarget(0.0f, 0.0f, 0.0f);
	m_window.GetGraphics().ClearDepthStencil();
	m_window.GetGraphics().BindDepthStencil();

	if (m_UIManager.GetCurrentScreenID() == ScreenType::GAME_HUD)
	{
		m_levelManager.DrawCurrentLevel(m_window.GetGraphics());
	}

	m_window.GetGraphics().ClearDepthStencil();
	m_UIManager.Draw(m_window.GetGraphics());

	m_window.GetGraphics().RenderFrame();
}