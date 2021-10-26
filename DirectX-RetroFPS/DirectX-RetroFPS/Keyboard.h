#pragma once
#include "KeyboardEvent.h"
#include <queue>

class Keyboard
{
public:
	Keyboard();

	bool IsKeyPressed(const unsigned char keycode);
	bool IsEventBufferEmpty();
	bool IsCharacterBufferEmpty();

	KeyboardEvent ReadKey();
	unsigned char ReadChar();

	void OnKeyPressed(const unsigned char key);
	void OnKeyHeld(const unsigned char key);
	void OnKeyReleased(const unsigned char key);

	void OnCharacter(const unsigned char key);

private:
	bool m_keyStates[256];
	
	std::queue<KeyboardEvent> m_eventBuffer;
	std::queue<unsigned char> m_characterBuffer;
};