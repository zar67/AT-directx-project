#include "GameHUDScreen.h"

GameHUDScreen::GameHUDScreen(Graphics& graphics)
{
	m_screenType = ScreenType::GAME_HUD;

	std::unique_ptr<AnimatedImageElement> hudWeapons = std::make_unique<AnimatedImageElement>(graphics, "Assets\\UI\\doom_weapons_ui.png", 8, 2);
	hudWeapons->SetOffset(Vector(0.0f, 0.0f, 6.0f));
	hudWeapons->GetTransform().ApplyScalar(8.0f, 6.0f, 1.0f);
	hudWeapons->ChangeSprite(0);
	m_pHUDWeapons = hudWeapons.get();

	AddElement(std::move(hudWeapons), graphics.GetCamera());

	std::unique_ptr<ImageElement> hudBackground = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_hud.png");
	hudBackground->SetOffset(Vector(0.0f, -3.75f, 5.0f));
	hudBackground->GetTransform().ApplyScalar(6.0f, 1.25f, 1.0f);

	AddElement(std::move(hudBackground), graphics.GetCamera());

	std::unique_ptr<ImageElement> crosshair = std::make_unique<ImageElement>(graphics, "Assets\\UI\\crosshair.png");
	crosshair->SetOffset(Vector(0.0f, 0.0f, 5.0f));
	crosshair->GetTransform().ApplyScalar(0.2f, 0.2f, 1.0f);

	AddElement(std::move(crosshair), graphics.GetCamera());

	std::unique_ptr<AnimatedImageElement> hudCharacter = std::make_unique<AnimatedImageElement>(graphics, "Assets\\UI\\doom_hud_character.png", 5, 1);
	hudCharacter->SetOffset(Vector(-0.54f, -3.375f, 4.0f));
	hudCharacter->GetTransform().ApplyScalar(0.55f, 0.55f, 1.0f);
	hudCharacter->ChangeSprite(0);
	m_pCharacterDisplay = hudCharacter.get();

	AddElement(std::move(hudCharacter), graphics.GetCamera());

	std::unique_ptr<TextElement> armorText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	armorText->GetTransform().ApplyTranslation(Vector(55.0f, 510.0f, 4.0f));
	armorText->SetText("100");
	m_pArmorText = armorText.get();

	AddElement(std::move(armorText), graphics.GetCamera());

	std::unique_ptr<TextElement> healthText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	healthText->GetTransform().ApplyTranslation(Vector(190.0f, 510.0f, 4.0f));
	healthText->SetText("100");
	m_pHealthText = healthText.get();

	AddElement(std::move(healthText), graphics.GetCamera());

	std::unique_ptr<TextElement> pistolText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	pistolText->GetTransform().ApplyTranslation(Vector(650.0f, 480.0f, 4.0f));
	pistolText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	pistolText->SetText("9999");
	m_pPistolBulletsText = pistolText.get();

	AddElement(std::move(pistolText), graphics.GetCamera());

	std::unique_ptr<TextElement> rifleText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	rifleText->GetTransform().ApplyTranslation(Vector(650.0f, 505.0f, 4.0f));
	rifleText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	rifleText->SetText("9999");
	m_pRifleBulletsText = rifleText.get();

	AddElement(std::move(rifleText), graphics.GetCamera());

	std::unique_ptr<TextElement> shotgunText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	shotgunText->GetTransform().ApplyTranslation(Vector(650.0f, 530.0f, 4.0f));
	shotgunText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	shotgunText->SetText("9999");
	m_pShotgunBulletsText = shotgunText.get();

	AddElement(std::move(shotgunText), graphics.GetCamera());

	std::unique_ptr<TextElement> cannonText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	cannonText->GetTransform().ApplyTranslation(Vector(650.0f, 555.0f, 4.0f));
	cannonText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	cannonText->SetText("9999");
	m_pCannonBulletsText = cannonText.get();

	AddElement(std::move(cannonText), graphics.GetCamera());

	std::unique_ptr<ImageElement> hudKey = std::make_unique<ImageElement>(graphics, "Assets\\UI\\key.png");
	hudKey->SetOffset(Vector(1.95f, -3.35f, 4.0f));
	hudKey->GetTransform().ApplyScalar(0.15f, 0.25f, 1.0f);
	m_pKeyImage = hudKey.get();

	AddElement(std::move(hudKey), graphics.GetCamera());
}

void GameHUDScreen::UpdateHUD(Player& player)
{
	int characterIndex = 4 - (int)player.GetHealth().GetCurrentValue() / ((int)player.GetHealth().GetMaxValue() / 4);
	characterIndex--;

	if (characterIndex < 0)
	{
		characterIndex = 0;
	}

	if (player.GetHealth().GetCurrentValue() == 0)
	{
		characterIndex = 4;
	}

	m_pCharacterDisplay->ChangeSprite(characterIndex);

	m_pHealthText->SetText(std::to_string((int)player.GetHealth().GetCurrentValue()));
	m_pArmorText->SetText(std::to_string((int)player.GetArmor().GetCurrentValue()));

	m_pKeyImage->SetActive(player.HasKey());
}