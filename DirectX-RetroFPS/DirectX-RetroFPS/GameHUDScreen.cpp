#include "GameHUDScreen.h"
#include "ImageElement.h"

GameHUDScreen::GameHUDScreen(Graphics& graphics)
{
	m_screenType = ScreenType::GAME_HUD;

	std::unique_ptr<ImageElement> hudBackground = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_hud.png");
	hudBackground->SetOffset(Vector(0.0f, 0.0f, 5.0f));
	hudBackground->GetTransform().ApplyScalar(1.0f, 1.0f, 1.0f);

	AddElement(std::move(hudBackground), graphics.GetCamera());
}