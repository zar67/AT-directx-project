#include "MainMenuScreen.h"

#include "ImageElement.h"

MainMenuScreen::MainMenuScreen(Graphics& graphics)
{
	m_screenType = ScreenType::MAIN_MENU;

	std::unique_ptr<ImageElement> titleElement = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_title.png");
	titleElement->SetOffset(Vector(0.0f, 1.2f, 5.0f));
	titleElement->GetTransform().ApplyScalar(3.0f, 3.0f, 3.0f);

	AddElement(std::move(titleElement), graphics.GetCamera());
}

ScreenType MainMenuScreen::HandleInput(Input& input)
{
	if (input.GetKeyboard().IsKeyDown(' '))
	{
		return ScreenType::GAME_HUD;
	}

	return m_screenType;
}