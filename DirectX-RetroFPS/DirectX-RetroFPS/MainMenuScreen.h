#pragma once

#include "Screen.h"

#include "ButtonElement.h"

class MainMenuScreen : public Screen
{
public:
	MainMenuScreen(Graphics& graphics);
	virtual ~MainMenuScreen() = default;

	virtual ScreenType HandleInput(Input& input) override;

private:
	ButtonElement* m_pPlayButton = nullptr;
	ButtonElement* m_pQuitButton = nullptr;
};