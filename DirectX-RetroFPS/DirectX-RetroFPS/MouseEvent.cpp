#include "MouseEvent.h"

MouseEvent::MouseEvent()
{
	m_type = EventType::Invalid;
	m_isLeftPressed = false;
	m_isRightPressed = false;
	m_xPosition = 0;
	m_yPosition = 0;
}

MouseEvent::MouseEvent(const EventType type, bool isLeftPressed, bool isRightPressed, int xPos, int yPos)
{
	m_type = type;
	m_isLeftPressed = isLeftPressed;
	m_isRightPressed = isRightPressed;
	m_xPosition = xPos;
	m_yPosition = yPos;
}

MouseEvent::EventType MouseEvent::GetType()
{
	return m_type;
}

std::pair<int, int> MouseEvent::GetPos()
{
	return std::pair<int, int>(m_xPosition, m_yPosition);
}

int MouseEvent::GetXPos()
{
	return m_xPosition;
}

int MouseEvent::GetYPos()
{
	return m_yPosition;
}

bool MouseEvent::IsLeftPressed()
{
	return m_isLeftPressed;
}

bool MouseEvent::IsRightPressed()
{
	return m_isRightPressed;
}