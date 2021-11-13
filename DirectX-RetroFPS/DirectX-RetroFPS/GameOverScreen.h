#pragma once

#include "Screen.h"

#include "ButtonElement.h"

class GameOverScreen : public Screen
{
public:
	GameOverScreen(Graphics& graphics);
	~GameOverScreen() = default;

	virtual ScreenType HandleInput(Input & input) override;

private:
	ButtonElement* m_pPlayButton = nullptr;
	ButtonElement* m_pMenuButton = nullptr;
	ButtonElement* m_pQuitButton = nullptr;
};