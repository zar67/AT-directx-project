#pragma once

#include <map>

#include "Screen.h"
#include "Input.h"

class UIManager
{
public:
	UIManager(Graphics& graphics);
	~UIManager() = default;

	void HandleInput(Input& input);
	void Update(float deltaTime);
	void Draw(Graphics& graphics);

	void GoToScreen(ScreenType screen);
	ScreenType GetCurrentScreenID();

private:
	ScreenType m_currentScreen = ScreenType::MAIN_MENU;
	std::map<ScreenType, std::unique_ptr<Screen>> m_screens;
};