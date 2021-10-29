#include "Keyboard.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		m_keyStates[i] = false;
	}
}

void Keyboard::HandleMessages(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_KEYUP:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			OnKeyReleased(keycode);
			break;
		}
		case WM_KEYDOWN:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			const bool wasPressed = lparam & 0x40000000;

			if (wasPressed)
			{
				OnKeyHeld(keycode);
			}
			else
			{
				OnKeyPressed(keycode);
			}

			break;
		}
		case WM_CHAR:
		{
			unsigned char keycode = static_cast<unsigned char>(wparam);
			OnCharacter(keycode);
			break;
		}
	}
}

bool Keyboard::IsKeyPressed(const unsigned char keycode)
{
	return m_keyStates[keycode];
}

bool Keyboard::IsEventBufferEmpty()
{
	return m_eventBuffer.empty();
}

bool Keyboard::IsCharacterBufferEmpty()
{
	return m_characterBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey()
{
	if (IsEventBufferEmpty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent keyboardEvent = m_eventBuffer.front();
		m_eventBuffer.pop();
		return keyboardEvent;
	}
}

unsigned char Keyboard::ReadChar()
{
	if (IsCharacterBufferEmpty())
	{
		return 0u;
	}
	else
	{
		unsigned char character = m_characterBuffer.front();
		m_characterBuffer.pop();
		return character;
	}
}

void Keyboard::OnKeyPressed(const unsigned char key)
{
	m_keyStates[key] = true;
	m_eventBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void Keyboard::OnKeyHeld(const unsigned char key)
{
	m_keyStates[key] = true;
	m_eventBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Hold, key));
}

void Keyboard::OnKeyReleased(const unsigned char key)
{
	m_keyStates[key] = false;
	m_eventBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void Keyboard::OnCharacter(const unsigned char key)
{
	m_characterBuffer.push(key);
}