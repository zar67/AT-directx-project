#pragma once
#include <optional>

class MouseEvent
{
public:
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
		Invalid
	};

	MouseEvent();
	MouseEvent(const EventType type, bool isLeftPressed, bool isRightPressed, int xPos, int yPos);

	EventType GetType(); 
	std::pair<int, int> GetPos();
	int GetXPos();
	int GetYPos();

	bool IsLeftPressed();
	bool IsRightPressed();

private:
	EventType m_type;
	bool m_isLeftPressed;
	bool m_isRightPressed;
	int m_xPosition;
	int m_yPosition;
};