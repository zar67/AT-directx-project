#include "Mouse.h"

void Mouse::HandleMessages(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_MOUSEMOVE:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnMouseMove(points.x, points.y);
		}
		case WM_LBUTTONDOWN:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnLeftPressed(points.x, points.y);
		}
		case WM_LBUTTONUP:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnLeftReleased(points.x, points.y);
		}
		case WM_RBUTTONDOWN:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnRightPressed(points.x, points.y);
		}
		case WM_RBUTTONUP:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnRightReleased(points.x, points.y);
		}
		case WM_MBUTTONDOWN:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnMiddlePressed(points.x, points.y);
		}
		case WM_MBUTTONUP:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnMiddleReleased(points.x, points.y);
		}
		case WM_MOUSEHWHEEL:
		{
			POINTS points = MAKEPOINTS(lparam);
			if (GET_WHEEL_DELTA_WPARAM(wparam) > 0)
			{
				OnWheelUp(points.x, points.y);
			}
			else if (GET_WHEEL_DELTA_WPARAM(wparam) < 0)
			{
				OnWheelDown(points.x, points.y);
			}
		}
	}
}

std::pair<int, int> Mouse::GetPos()
{
	return std::pair<int, int>(m_xPosition, m_yPosition);
}

int Mouse::GetXPos()
{
	return m_xPosition;
}

int Mouse::GetYPos()
{
	return m_yPosition;
}

bool Mouse::IsLeftPressed()
{
	return m_isLeftPressed;
}

bool Mouse::IsRightPressed()
{
	return m_isRightPressed;
}

MouseEvent Mouse::Read()
{
	if (m_eventBuffer.size() > 0u)
	{
		MouseEvent e = m_eventBuffer.front();
		m_eventBuffer.pop();
		return e;
	}
	else
	{
		return MouseEvent();
	}
}

bool Mouse::IsEventBufferEmpty()
{
	return m_eventBuffer.empty();
}

void Mouse::Flush()
{
	m_eventBuffer = std::queue<MouseEvent>();
}

void Mouse::OnMouseMove(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isLeftPressed = true;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LPress, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnLeftHeld(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isLeftHeld = true;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LHold, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isLeftPressed = false;
	m_isLeftHeld = false;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isRightPressed = true;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnRightHeld(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isRightHeld = true;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RHold, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isRightPressed = false;
	m_isRightHeld = false;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMiddlePressed(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isMiddlePressed = true;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMiddleHeld(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isMiddleHeld = true;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::MHold, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMiddleReleased(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_isMiddleHeld = false;
	m_isMiddlePressed = false;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::TrimBuffer()
{
	while (m_eventBuffer.size() > m_bufferSize)
	{
		m_eventBuffer.pop();
	}
}