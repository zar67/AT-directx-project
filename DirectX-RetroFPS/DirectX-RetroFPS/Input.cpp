#include "Input.h"

void Input::HandleMessages(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, int windowWidth, int windowHeight)
{
	m_keyboard.HandleMessages(message, wparam, lparam);
	m_mouse.HandleMessages(hWnd, message, wparam, lparam, windowWidth, windowHeight);
}

void Input::UpdateStates()
{
	m_mouse.DetectHeldButtons();
}

Keyboard& Input::GetKeyboard()
{
	return m_keyboard;
}

Mouse& Input::GetMouse()
{
	return m_mouse;
}
