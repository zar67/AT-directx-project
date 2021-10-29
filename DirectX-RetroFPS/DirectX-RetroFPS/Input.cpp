#include "Input.h"
#include <string>
#include <iostream>

void Input::HandleMessages(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, int windowWidth, int windowHeight)
{
	m_keyboard.HandleMessages(message, wparam, lparam);
	m_mouse.HandleMessages(hWnd, message, wparam, lparam, windowWidth, windowHeight);
}

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

	while (!m_mouse.IsEventBufferEmpty())
	{
		MouseEvent mouseEvent = m_mouse.Read();
	}

	m_keyboard.ResetPressedKeys();
	m_mouse.ResetPressedButtons();
}

Keyboard& Input::GetKeyboard()
{
	return m_keyboard;
}

Mouse& Input::GetMouse()
{
	return m_mouse;
}
