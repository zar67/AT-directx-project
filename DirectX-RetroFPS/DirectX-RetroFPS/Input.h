#pragma once
#include "Keyboard.h"

class Input
{
public:
	Input() = default;
	~Input() = default;

	void Update();

	Keyboard* GetKeyboard();

private:
	Keyboard m_keyboard;
};

