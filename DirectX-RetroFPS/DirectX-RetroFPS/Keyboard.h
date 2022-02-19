#pragma once

#include <queue>
#include <Windows.h>

#include "KeyboardEvent.h"

class Keyboard
{
public:
	enum class KeyState
	{
		PRESSED,
		HELD,
		NOT_PRESSED
	};
public:
	Keyboard();

	void HandleMessages(UINT message, WPARAM wparam, LPARAM lparam);

	void DetectedHeldKeys();

	KeyState GetKeyState(const unsigned char keycode);
	bool IsKeyDown(const unsigned char keycode);

	bool IsEventBufferEmpty();
	bool IsCharacterBufferEmpty();

	KeyboardEvent ReadKey();
	unsigned char ReadChar();

private:
	void OnKeyPressed(const unsigned char key);
	void OnKeyHeld(const unsigned char key);
	void OnKeyReleased(const unsigned char key);

	void OnCharacter(const unsigned char key);

	KeyState m_keyStates[256];
	
	std::queue<KeyboardEvent> m_eventBuffer;
	std::queue<unsigned char> m_characterBuffer;
};