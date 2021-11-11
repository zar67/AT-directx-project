#pragma once

#include "Screen.h"
#include <map>

class UIManager
{
public:
	enum class ScreenID
	{
		MAIN_MENU,
		GAME_HUD,
		GAME_OVER
	};
public:
	UIManager(Graphics& graphics);
	~UIManager() = default;

	void Update(float deltaTime);
	void Draw(Graphics& graphics);

	void GoToScreen(ScreenID screen);
	ScreenID GetCurrentScreenID();

private:
	ScreenID m_currentScreen = ScreenID::MAIN_MENU;

	std::map<ScreenID, std::unique_ptr<Screen>> m_screens;
};