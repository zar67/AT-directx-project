#pragma once

class MouseEvent
{
public:
	enum class ButtonState
	{
		NOT_PRESSED,
		PRESSED,
		HELD
	};

	enum class EventType
	{
		INVALID,
		L_PRESS,
		L_HOLD,
		L_RELEASE,
		R_PRESS,
		R_HOLD,
		R_RELEASE,
		M_PRESS,
		M_HOLD,
		M_RELEASE,
		WHEEL_UP,
		WHEEL_DOWN,
		MOVE,
		ENTER_WINDOW,
		LEAVE_WINDOW
	};

	MouseEvent();
	MouseEvent(const EventType type, ButtonState leftButtonState, ButtonState rightButtonState, ButtonState middleButtonState, int xPos, int yPos);

	EventType GetType();
	int GetXPos();
	int GetYPos();

	ButtonState GetLeftButtonState();
	ButtonState GetRightButtonState();
	ButtonState GetMiddleButtonState();

private:
	EventType m_type;

	ButtonState m_leftButtonState;
	ButtonState m_rightButtonState;
	ButtonState m_middleButtonState;

	int m_xPosition;
	int m_yPosition;
};