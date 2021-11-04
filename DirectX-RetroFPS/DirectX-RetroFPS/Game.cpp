#include "Game.h"
#include "CollisionUtilities.h"
#include <iostream>

Game::Game() :
	m_window(800, 600, IDS_GAMENAME, IDI_MAINICON),
	m_levelManager(m_window.GetGraphics())
{
	m_light = std::make_unique<Light>(m_window.GetGraphics());
	m_light->GetTransform().ApplyScalar(0.5f, 0.5f, 0.5f);
	m_light->GetTransform().ApplyTranslation(4.0f, 0.0f, 2.0f);
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

	if (!m_isPaused)
	{
		m_window.GetGraphics().GetCamera()->Update(deltaTime, m_window.GetInput(), m_window.GetWidth(), m_window.GetHeight());
		HandleCollision();
	}
}

void Game::HandleInput()
{
	KeyboardEvent keyboardEvent = m_window.GetInput().GetKeyboard().ReadKey();
	while (keyboardEvent.GetType() != KeyboardEvent::EventType::Invalid)
	{
		if (keyboardEvent.GetKeyCode() == VK_ESCAPE && keyboardEvent.GetType() == KeyboardEvent::EventType::Press)
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
	while (mouseEvent.GetType() != MouseEvent::EventType::Invalid)
	{
		// Handle Mouse Event
		mouseEvent = m_window.GetInput().GetMouse().Read();
	}
}

void Game::HandleCollision()
{
	std::cout << "FRAME BEGIN" << std::endl;
	Level* currentLevel = m_levelManager.GetCurrentLevel();
	for (int i = 0; i < currentLevel->GetGeometryCount(); i++)
	{
		DrawableBase* drawableA = currentLevel->GetGeometryAtIndex(i);
		CollisionUtilities::CollisionData collision = CollisionUtilities::IsColliding(drawableA->GetCollider(), m_window.GetGraphics().GetCamera()->GetCollider());
		if (collision.IsColliding)
		{
			std::cout << "--------------------" << std::endl;
			std::cout << "A Pos: (" << collision.ColliderA->GetTransform()->Position.x << "," << collision.ColliderA->GetTransform()->Position.y << "," << collision.ColliderA->GetTransform()->Position.z << "), B Pos: (" << collision.ColliderB->GetTransform()->Position.x << "," << collision.ColliderB->GetTransform()->Position.y << "," << collision.ColliderB->GetTransform()->Position.z << ")" << std::endl;
			CollisionUtilities::ResolveCollision(collision);
			std::cout << "--------------------" << std::endl;
			std::cout << "A Pos: (" << collision.ColliderA->GetTransform()->Position.x << "," << collision.ColliderA->GetTransform()->Position.y << "," << collision.ColliderA->GetTransform()->Position.z << "), B Pos: (" << collision.ColliderB->GetTransform()->Position.x << "," << collision.ColliderB->GetTransform()->Position.y << "," << collision.ColliderB->GetTransform()->Position.z << ")" << std::endl;

		}
	}
}

void Game::Render()
{
	m_window.GetGraphics().ClearBuffer(0.0f, 0.0f, 0.0f);

	m_light->Bind(m_window.GetGraphics());

	m_light->Draw(m_window.GetGraphics());
	m_levelManager.DrawCurrentLevel(m_window.GetGraphics());

	m_window.GetGraphics().RenderFrame();
}