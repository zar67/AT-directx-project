#include "Input.h"
#include <string>
#include <iostream>

void Input::Update()
{
	while (!m_keyboard.IsCharacterBufferEmpty())
	{
		unsigned char keycode = m_keyboard.ReadChar();
	}

	while (!m_keyboard.IsEventBufferEmpty())
	{
		KeyboardEvent keyboardEvent = m_keyboard.ReadKey();
	}
}

Keyboard* Input::GetKeyboard()
{
	return &m_keyboard;
}
