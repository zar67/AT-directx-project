#pragma once
#include <Windows.h>
#include "Keyboard.h"
#include "Mouse.h"

class Input
{
public:
	Input() = default;
	~Input() = default;

	void HandleMessages(UINT message, WPARAM wparam, LPARAM lparam);
	void Update();

	Keyboard& GetKeyboard();
	Mouse& GetMouse();

private:
	Keyboard m_keyboard;
	Mouse m_mouse;
};

