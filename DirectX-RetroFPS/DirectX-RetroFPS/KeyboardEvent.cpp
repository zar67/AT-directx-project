#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
{
	m_type = EventType::INVALID;
	m_key = 0u;
}

KeyboardEvent::KeyboardEvent(const KeyboardEvent::EventType type, const unsigned char key)
{
	m_type = type;
	m_key = key;
}

KeyboardEvent::EventType KeyboardEvent::GetType()
{
	return m_type;
}

unsigned char KeyboardEvent::GetKeyCode()
{
	return m_key;
}