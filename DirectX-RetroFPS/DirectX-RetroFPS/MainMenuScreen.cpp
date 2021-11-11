#include "MainMenuScreen.h"

#include "ImageElement.h"

MainMenuScreen::MainMenuScreen(Graphics& graphics)
{
	m_screenType = ScreenType::MAIN_MENU;

	std::unique_ptr<ImageElement> titleElement = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_title.png");
	titleElement->SetOffset(Vector(0.0f, 1.2f, 5.0f));
	titleElement->GetTransform().ApplyScalar(3.0f, 3.0f, 3.0f);

	AddElement(std::move(titleElement), graphics.GetCamera());

	std::unique_ptr<ButtonElement> playButtonElement = std::make_unique<ButtonElement>(graphics, "Assets\\UI\\doom_button.png");
	playButtonElement->SetOffset(Vector(0.0f, -1.5f, 4.0f));
	playButtonElement->GetTransform().ApplyScalar(1.0f, 0.5f, 2.0f);
	playButtonElement->Select();
	m_pPlayButton = playButtonElement.get();

	AddElement(std::move(playButtonElement), graphics.GetCamera());

	std::unique_ptr<ButtonElement> quitButtonElement = std::make_unique<ButtonElement>(graphics, "Assets\\UI\\doom_button.png");
	quitButtonElement->SetOffset(Vector(0.0f, -3.0f, 4.0f));
	quitButtonElement->GetTransform().ApplyScalar(1.0f, 0.5f, 2.0f);
	m_pQuitButton = quitButtonElement.get();

	AddElement(std::move(quitButtonElement), graphics.GetCamera());
}

ScreenType MainMenuScreen::HandleInput(Input& input)
{
	if (input.GetKeyboard().IsKeyDown(' '))
	{
		if (m_pPlayButton->IsSelected())
		{
			return ScreenType::GAME_HUD;
		}
		else if (m_pQuitButton->IsSelected())
		{
			exit(0);
		}
	}

	if (input.GetKeyboard().GetKeyState('S') == Keyboard::KeyState::PRESSED &&
		m_pPlayButton->IsSelected())
	{
		m_pPlayButton->Deselect();
		m_pQuitButton->Select();
	}
	else if (input.GetKeyboard().GetKeyState('W') == Keyboard::KeyState::PRESSED && 
		m_pQuitButton->IsSelected())
	{
		m_pQuitButton->Deselect();
		m_pPlayButton->Select();
	}

	return m_screenType;
}