#include "Input.h"
#include <string>
#include <iostream>

void Input::HandleMessages(UINT message, WPARAM wparam, LPARAM lparam)
{
	m_keyboard.HandleMessages(message, wparam, lparam);
	m_mouse.HandleMessages(message, wparam, lparam);
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
		if (mouseEvent.GetType() == MouseEvent::EventType::Move)
		{
			std::cout << "Mouse Position: (" << mouseEvent.GetXPos() << "," << mouseEvent.GetYPos() << ")" << std::endl;
		}
	}
}

Keyboard& Input::GetKeyboard()
{
	return m_keyboard;
}

Mouse& Input::GetMouse()
{
	return m_mouse;
}
