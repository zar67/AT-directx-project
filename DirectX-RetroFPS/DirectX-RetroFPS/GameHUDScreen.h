#pragma once

#include "Screen.h"
#include "Player.h"
#include "AnimatedImageElement.h"
#include "TextElement.h"

class GameHUDScreen : public Screen
{
public:
	GameHUDScreen(Graphics& graphics);

	void UpdateHUD(Player& player);

private:
	AnimatedImageElement* m_pCharacterDisplay = nullptr;
	TextElement* m_pHealthText = nullptr;
	TextElement* m_pArmorText = nullptr;
};