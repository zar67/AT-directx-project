#pragma once

#include "Screen.h"
#include "Player.h"
#include "AnimatedImageElement.h"

class GameHUDScreen : public Screen
{
public:
	GameHUDScreen(Graphics& graphics);

	void UpdateHUD(Player& player);

	AnimatedImageElement* m_characterDisplay = nullptr;
};