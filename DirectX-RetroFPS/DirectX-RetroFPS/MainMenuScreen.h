#pragma once

#include "Screen.h"

class MainMenuScreen : public Screen
{
public:
	MainMenuScreen(Graphics& graphics);

	virtual ScreenType HandleInput(Input& input) override;
};