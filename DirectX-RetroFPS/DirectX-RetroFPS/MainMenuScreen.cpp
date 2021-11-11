#include "MainMenuScreen.h"

#include "ImageElement.h"

MainMenuScreen::MainMenuScreen(Graphics& graphics)
{
	std::unique_ptr<ImageElement> titleElement = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_title.png");
	titleElement->SetOffset(Vector(0.0f, 1.2f, 5.0f));
	titleElement->GetTransform().ApplyScalar(3.0f, 3.0f, 3.0f);

	AddElement(std::move(titleElement), graphics.GetCamera());
};