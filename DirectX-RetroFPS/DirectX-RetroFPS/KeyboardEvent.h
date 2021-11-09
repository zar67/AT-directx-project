#pragma once

class KeyboardEvent
{
public:
	enum class EventType
	{
		INVALID,
		PRESS,
		HOLD,
		RELEASE
	};

	KeyboardEvent();
	KeyboardEvent(const EventType type, const unsigned char key);

	EventType GetType();
	unsigned char GetKeyCode();

private:
	EventType m_type;
	unsigned char m_key;
};