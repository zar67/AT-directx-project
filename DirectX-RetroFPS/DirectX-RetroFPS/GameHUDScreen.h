#pragma once

#include "Screen.h"
#include "Player.h"
#include "AnimatedImageElement.h"
#include "ImageElement.h"
#include "TextElement.h"

class GameHUDScreen : public Screen
{
public:
	GameHUDScreen(Graphics& graphics);

	void UpdateHUD(Player& player);

private:
	AnimatedImageElement* m_pCharacterDisplay = nullptr;
	ImageElement* m_pKeyImage = nullptr;

	TextElement* m_pHealthText = nullptr;
	TextElement* m_pArmorText = nullptr;

	TextElement* m_pPistolBulletsText = nullptr;
	TextElement* m_pRifleBulletsText = nullptr;
	TextElement* m_pShotgunBulletsText = nullptr;
	TextElement* m_pCannonBulletsText = nullptr;
};