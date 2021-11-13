#include "GameOverScreen.h"

#include "ImageElement.h"
#include "TextElement.h"

GameOverScreen::GameOverScreen(Graphics& graphics)
{
	m_screenType = ScreenType::GAME_OVER;

	std::unique_ptr<TextElement> titleElement = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	titleElement->GetTransform().ApplyTranslation(Vector(40.0f, 80.0f, 5.0f));
	titleElement->GetTransform().ApplyScalar(2.5f, 2.5f, 1.0f);
	titleElement->SetText("Game Over");

	AddElement(std::move(titleElement), graphics.GetCamera());

	std::unique_ptr<ButtonElement> playButtonElement = std::make_unique<ButtonElement>(graphics, "Assets\\UI\\doom_button.png");
	playButtonElement->SetOffset(Vector(0.0f, 0.0f, 4.0f));
	playButtonElement->GetTransform().ApplyScalar(1.5f, 0.5f, 1.0f);
	playButtonElement->Select();
	m_pPlayButton = playButtonElement.get();

	AddElement(std::move(playButtonElement), graphics.GetCamera());

	std::unique_ptr<ButtonElement> menuButtonElement = std::make_unique<ButtonElement>(graphics, "Assets\\UI\\doom_button.png");
	menuButtonElement->SetOffset(Vector(0.0f, -1.5f, 4.0f));
	menuButtonElement->GetTransform().ApplyScalar(1.5f, 0.5f, 1.0f);
	m_pMenuButton = menuButtonElement.get();

	AddElement(std::move(menuButtonElement), graphics.GetCamera());

	std::unique_ptr<ButtonElement> quitButtonElement = std::make_unique<ButtonElement>(graphics, "Assets\\UI\\doom_button.png");
	quitButtonElement->SetOffset(Vector(0.0f, -3.0f, 4.0f));
	quitButtonElement->GetTransform().ApplyScalar(1.5f, 0.5f, 1.0f);
	m_pQuitButton = quitButtonElement.get();

	AddElement(std::move(quitButtonElement), graphics.GetCamera());

	std::unique_ptr<TextElement> playText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	playText->GetTransform().ApplyTranslation(Vector(350.0f, 270.0f, 3.0f));
	playText->SetText("Play");

	AddElement(std::move(playText), graphics.GetCamera());

	std::unique_ptr<TextElement> menuText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	menuText->GetTransform().ApplyTranslation(Vector(350.0f, 381.5f, 3.0f));
	menuText->SetText("Menu");

	AddElement(std::move(menuText), graphics.GetCamera());

	std::unique_ptr<TextElement> quitText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	quitText->GetTransform().ApplyTranslation(Vector(350.0f, 494.5f, 3.0f));
	quitText->SetText("Quit");

	AddElement(std::move(quitText), graphics.GetCamera());
}

ScreenType GameOverScreen::HandleInput(Input& input)
{
	if (input.GetKeyboard().IsKeyDown(' '))
	{
		if (m_pPlayButton->IsSelected())
		{
			return ScreenType::GAME_HUD;
		}
		else if (m_pMenuButton->IsSelected())
		{
			return ScreenType::MAIN_MENU;
		}
		else if (m_pQuitButton->IsSelected())
		{
			exit(0);
		}
	}

	if (input.GetKeyboard().GetKeyState('S') == Keyboard::KeyState::PRESSED)
	{
		if (m_pPlayButton->IsSelected())
		{
			m_pPlayButton->Deselect();
			m_pMenuButton->Select();
		}
		else if (m_pMenuButton->IsSelected())
		{
			m_pMenuButton->Deselect();
			m_pQuitButton->Select();
		}
	}
	else if (input.GetKeyboard().GetKeyState('W') == Keyboard::KeyState::PRESSED)
	{
		if (m_pMenuButton->IsSelected())
		{
			m_pMenuButton->Deselect();
			m_pPlayButton->Select();
		}
		else if (m_pQuitButton->IsSelected())
		{
			m_pQuitButton->Deselect();
			m_pMenuButton->Select();
		}
	}

	return m_screenType;
}