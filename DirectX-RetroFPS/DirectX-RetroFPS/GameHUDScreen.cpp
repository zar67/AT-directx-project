#include "GameHUDScreen.h"

GameHUDScreen::GameHUDScreen(Graphics& graphics)
{
	m_screenType = ScreenType::GAME_HUD;

	std::unique_ptr<AnimatedImageElement> hudWeapons = std::make_unique<AnimatedImageElement>(graphics, "Assets\\UI\\doom_weapons_ui.png", 6, 2);
	hudWeapons->SetOffset(Vector(0.0f, 0.0f, 6.0f));
	hudWeapons->GetTransform().ApplyScalar(8.0f, 6.0f, 1.0f);
	hudWeapons->ChangeSprite(0);
	m_pHUDWeapons = hudWeapons.get();

	AddElement(std::move(hudWeapons), graphics.GetCamera());

	std::unique_ptr<ImageElement> hudBackground = std::make_unique<ImageElement>(graphics, "Assets\\UI\\doom_hud.png");
	hudBackground->SetOffset(Vector(0.0f, -3.75f, 5.0f));
	hudBackground->GetTransform().ApplyScalar(6.25f, 1.25f, 1.0f);

	AddElement(std::move(hudBackground), graphics.GetCamera());

	std::unique_ptr<ImageElement> crosshair = std::make_unique<ImageElement>(graphics, "Assets\\UI\\crosshair.png");
	crosshair->SetOffset(Vector(0.0f, 0.0f, 5.0f));
	crosshair->GetTransform().ApplyScalar(0.2f, 0.2f, 1.0f);

	AddElement(std::move(crosshair), graphics.GetCamera());

	std::unique_ptr<AnimatedImageElement> hudCharacter = std::make_unique<AnimatedImageElement>(graphics, "Assets\\UI\\character_hud.png", 5, 1);
	hudCharacter->SetOffset(Vector(-0.025f, -3.2f, 4.0f));
	hudCharacter->GetTransform().ApplyScalar(0.55f, 0.55f, 1.0f);
	hudCharacter->ChangeSprite(0);
	m_pCharacterDisplay = hudCharacter.get();

	AddElement(std::move(hudCharacter), graphics.GetCamera());

	std::unique_ptr<TextElement> armorText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	armorText->GetTransform().ApplyTranslation(Vector(80.0f, 500.0f, 4.0f));
	armorText->SetText("100");
	m_pArmorText = armorText.get();

	AddElement(std::move(armorText), graphics.GetCamera());

	std::unique_ptr<TextElement> healthText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	healthText->GetTransform().ApplyTranslation(Vector(215.0f, 500.0f, 4.0f));
	healthText->SetText("100");
	m_pHealthText = healthText.get();

	AddElement(std::move(healthText), graphics.GetCamera());

	std::unique_ptr<TextElement> pistolText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	pistolText->GetTransform().ApplyTranslation(Vector(675.0f, 482.0f, 4.0f));
	pistolText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	pistolText->SetText("999");
	m_pPistolBulletsText = pistolText.get();

	AddElement(std::move(pistolText), graphics.GetCamera());

	std::unique_ptr<TextElement> rifleText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	rifleText->GetTransform().ApplyTranslation(Vector(675.0f, 504.0f, 4.0f));
	rifleText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	rifleText->SetText("999");
	m_pRifleBulletsText = rifleText.get();

	AddElement(std::move(rifleText), graphics.GetCamera());

	std::unique_ptr<TextElement> shotgunText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	shotgunText->GetTransform().ApplyTranslation(Vector(675.0f, 526.0f, 4.0f));
	shotgunText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	shotgunText->SetText("999");
	m_pShotgunBulletsText = shotgunText.get();

	AddElement(std::move(shotgunText), graphics.GetCamera());

	std::unique_ptr<TextElement> cannonText = std::make_unique<TextElement>(graphics, "Assets\\Fonts\\doom_font.spritefont");
	cannonText->GetTransform().ApplyTranslation(Vector(675.0f, 548.0f, 4.0f));
	cannonText->GetTransform().ApplyScalar(0.7f, 0.75f, 0.75f);
	cannonText->SetText("999");
	m_pCannonBulletsText = cannonText.get();

	AddElement(std::move(cannonText), graphics.GetCamera());

	std::unique_ptr<ImageElement> hudKey = std::make_unique<ImageElement>(graphics, "Assets\\UI\\key.png");
	hudKey->SetOffset(Vector(1.85f, -3.3f, 4.0f));
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

	bool showShootImage = player.GetShooter().GetWeapon()->ShowShootImage();
	switch (player.GetShooter().GetWeapon()->GetType())
	{
		case WeaponType::FIST:
		{
			m_pHUDWeapons->ChangeSprite(showShootImage ? 1 : 0);
			break;
		}
		case WeaponType::CHAINSAW:
		{
			m_pHUDWeapons->ChangeSprite(showShootImage ? 11 : 10);
			break;
		}
		case WeaponType::PISTOL:
		{
			m_pHUDWeapons->ChangeSprite(showShootImage ? 3 : 2);
			break;
		}
		case WeaponType::RIFLE:
		{
			m_pHUDWeapons->ChangeSprite(showShootImage ? 5 : 4);
			break;
		}
		case WeaponType::SHOTGUN:
		{
			m_pHUDWeapons->ChangeSprite(showShootImage ? 7 : 6);
			break;
		}
		case WeaponType::CANNON:
		{
			m_pHUDWeapons->ChangeSprite(showShootImage ? 9 : 8);
			break;
		}
	}

	m_pHealthText->SetText(std::to_string((int)player.GetHealth().GetCurrentValue()));
	m_pArmorText->SetText(std::to_string((int)player.GetArmor().GetCurrentValue()));

	m_pPistolBulletsText->SetText(std::to_string(player.GetWeaponOfType(WeaponType::PISTOL)->GetBullets()));
	m_pRifleBulletsText->SetText(std::to_string(player.GetWeaponOfType(WeaponType::RIFLE)->GetBullets()));
	m_pShotgunBulletsText->SetText(std::to_string(player.GetWeaponOfType(WeaponType::SHOTGUN)->GetBullets()));
	m_pCannonBulletsText->SetText(std::to_string(player.GetWeaponOfType(WeaponType::CANNON)->GetBullets()));

	m_pKeyImage->SetActive(player.HasKey());
}