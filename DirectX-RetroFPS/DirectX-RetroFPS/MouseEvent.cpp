#include "MouseEvent.h"

MouseEvent::MouseEvent()
{
	m_type = EventType::INVALID;

	m_leftButtonState == ButtonState::NOT_PRESSED;
	m_rightButtonState == ButtonState::NOT_PRESSED;
	m_middleButtonState == ButtonState::NOT_PRESSED;

	m_xPosition = 0;
	m_yPosition = 0;
}

MouseEvent::MouseEvent(const EventType type, ButtonState leftButtonState, ButtonState rightButtonState, ButtonState middleButtonState, int xPos, int yPos)
{
	m_type = type;

	m_leftButtonState == leftButtonState;
	m_rightButtonState == rightButtonState;
	m_middleButtonState == middleButtonState;

	m_xPosition = xPos;
	m_yPosition = yPos;
}

MouseEvent::EventType MouseEvent::GetType()
{
	return m_type;
}

int MouseEvent::GetXPos()
{
	return m_xPosition;
}

int MouseEvent::GetYPos()
{
	return m_yPosition;
}

MouseEvent::ButtonState MouseEvent::GetLeftButtonState()
{
	return m_leftButtonState;
}

MouseEvent::ButtonState MouseEvent::GetRightButtonState()
{
	return m_rightButtonState;
}

MouseEvent::ButtonState MouseEvent::GetMiddleButtonState()
{
	return m_middleButtonState;
}