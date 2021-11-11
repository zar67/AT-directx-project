#include "MainMenuScreen.h"

#include "ImageElement.h"

MainMenuScreen::MainMenuScreen(Graphics& graphics)
{
	std::unique_ptr<ImageElement> titleElement = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_title.png");
	titleElement->GetTransform().ApplyScalar(2.0f, 2.0f, 2.0f);

	AddElement(std::move(titleElement), graphics.GetCamera());
};