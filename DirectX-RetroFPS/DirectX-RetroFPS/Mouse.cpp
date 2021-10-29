#include "Mouse.h"

void Mouse::HandleMessages(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, int windowWidth, int windowHeight)
{
	switch (message)
	{
		case WM_MOUSEMOVE:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnMouseMove(points.x, points.y);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnLeftPressed(points.x, points.y);
			break;
		}
		case WM_LBUTTONUP:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnLeftReleased(points.x, points.y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnRightPressed(points.x, points.y);
			break;
		}
		case WM_RBUTTONUP:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnRightReleased(points.x, points.y);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnMiddlePressed(points.x, points.y);
			break;
		}
		case WM_MBUTTONUP:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnMiddleReleased(points.x, points.y);
			break;
		}
		case WM_MOUSEHWHEEL:
		{
			POINTS points = MAKEPOINTS(lparam);
			OnWheelDelta(points.x, points.y, GET_WHEEL_DELTA_WPARAM(wparam));
			break;
		}
	}
}

void Mouse::ResetPressedButtons()
{
	if (m_leftButtonState == MouseEvent::ButtonState::PRESSED)
	{
		m_leftButtonState == MouseEvent::ButtonState::NOT_PRESSED;
	}

	if (m_rightButtonState == MouseEvent::ButtonState::PRESSED)
	{
		m_rightButtonState == MouseEvent::ButtonState::NOT_PRESSED;
	}

	if (m_middleButtonState == MouseEvent::ButtonState::PRESSED)
	{
		m_middleButtonState == MouseEvent::ButtonState::NOT_PRESSED;
	}
}

bool Mouse::IsInWindow()
{
	return m_isInWindow;
}

int Mouse::GetXPos()
{
	return m_xPosition;
}

int Mouse::GetYPos()
{
	return m_yPosition;
}

MouseEvent::ButtonState Mouse::GetLeftButtonState()
{
	return m_leftButtonState;
}

MouseEvent::ButtonState Mouse::GetRightButtonState()
{
	return m_rightButtonState;
}

MouseEvent::ButtonState Mouse::GetMiddleButtonState()
{
	return m_middleButtonState;
}

bool Mouse::IsLeftButtonDown()
{
	return m_leftButtonState == MouseEvent::ButtonState::PRESSED || m_leftButtonState == MouseEvent::ButtonState::HELD;
}

bool Mouse::IsRightButtonDown()
{
	return m_rightButtonState == MouseEvent::ButtonState::PRESSED || m_rightButtonState == MouseEvent::ButtonState::HELD;
}

bool Mouse::IsMiddleButtonDown()
{
	return m_middleButtonState == MouseEvent::ButtonState::PRESSED || m_middleButtonState == MouseEvent::ButtonState::HELD;
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

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_leftButtonState = MouseEvent::ButtonState::PRESSED;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LPress, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnLeftHeld(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_leftButtonState = MouseEvent::ButtonState::HELD;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LHold, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_leftButtonState = MouseEvent::ButtonState::NOT_PRESSED;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_rightButtonState = MouseEvent::ButtonState::PRESSED;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnRightHeld(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_rightButtonState = MouseEvent::ButtonState::HELD;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RHold, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_rightButtonState = MouseEvent::ButtonState::NOT_PRESSED;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMiddlePressed(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_middleButtonState = MouseEvent::ButtonState::PRESSED;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMiddleHeld(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_middleButtonState = MouseEvent::ButtonState::HELD;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::MHold, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMiddleReleased(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_middleButtonState = MouseEvent::ButtonState::NOT_PRESSED;

	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y)
{
	m_xPosition = x;
	m_yPosition = y;
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnWheelDelta(int x, int y, int delta)
{
	m_wheelDeltaCarry += delta;

	while (m_wheelDeltaCarry >= WHEEL_DELTA)
	{
		m_wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}

	while (m_wheelDeltaCarry <= -WHEEL_DELTA)
	{
		m_wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}

void Mouse::OnMouseEnterWindow()
{
	m_isInWindow = true;
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::EnterWindow, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMouseLeaveWindow()
{
	m_isInWindow = false;
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LeaveWindow, m_leftButtonState, m_rightButtonState, m_middleButtonState, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::TrimBuffer()
{
	while (m_eventBuffer.size() > m_bufferSize)
	{
		m_eventBuffer.pop();
	}
}