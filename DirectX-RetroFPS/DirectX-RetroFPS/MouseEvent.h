#pragma once
#include <optional>

class MouseEvent
{
public:
	enum class ButtonState
	{
		PRESSED,
		HELD,
		NOT_PRESSED
	};

	enum class EventType
	{
		LPress,
		LHold,
		LRelease,
		RPress,
		RHold,
		RRelease,
		MPress,
		MHold,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		EnterWindow,
		LeaveWindow,
		Invalid
	};

	MouseEvent();
	MouseEvent(const EventType type, ButtonState leftButtonState, ButtonState rightButtonState, ButtonState middleButtonState, int xPos, int yPos);

	EventType GetType(); 
	std::pair<int, int> GetPos();
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