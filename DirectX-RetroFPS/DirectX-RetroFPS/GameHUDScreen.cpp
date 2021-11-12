#include "GameHUDScreen.h"
#include "ImageElement.h"

GameHUDScreen::GameHUDScreen(Graphics& graphics)
{
	m_screenType = ScreenType::GAME_HUD;

	std::unique_ptr<ImageElement> hudBackground = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_hud.png");
	hudBackground->SetOffset(Vector(0.0f, -3.75f, 5.0f));
	hudBackground->GetTransform().ApplyScalar(6.0f, 1.25f, 1.0f);

	AddElement(std::move(hudBackground), graphics.GetCamera());

	std::unique_ptr<AnimatedImageElement> hudCharacter = std::make_unique<AnimatedImageElement>(graphics, "Assets\\UI\\doom_hud_character.png", 5, 1);
	hudCharacter->SetOffset(Vector(-0.54f, -3.375f, 4.0f));
	hudCharacter->GetTransform().ApplyScalar(0.55f, 0.55f, 1.0f);
	hudCharacter->ChangeSprite(0);
	m_characterDisplay = hudCharacter.get();

	AddElement(std::move(hudCharacter), graphics.GetCamera());
}

void GameHUDScreen::UpdateHUD(Player& player)
{
	int characterIndex = (int)player.GetHealth().GetCurrentHealth() / ((int)player.GetHealth().GetMaxHealth() / 5);
	m_characterDisplay->ChangeSprite(characterIndex);
}