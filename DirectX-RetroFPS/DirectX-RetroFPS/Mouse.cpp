#include "Mouse.h"

void Mouse::HandleMessages(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, int windowWidth, int windowHeight)
{
	switch (message)
	{
		case WM_MOUSEMOVE:
		{
			POINTS points = MAKEPOINTS(lparam);

			if (points.x >= 0 && points.x < windowWidth &&
				points.y >= 0 && points.y < windowHeight)
			{
				OnMouseMove(points.x, points.y);

				if (!m_isInWindow)
				{
					// Ensures even if the mouse leaves the window region we recieve messages.
					SetCapture(hWnd);

					OnMouseEnterWindow();
				}
			}
			else
			{
				// Perform drag even if outside of the window.
				if (m_isLeftPressed || m_isRightPressed || m_isMiddlePressed)
				{
					OnMouseMove(points.x, points.y);
				}
				else
				{
					ReleaseCapture();
					OnMouseLeaveWindow();
				}
			}

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

bool Mouse::IsInWindow()
{
	return m_isInWindow;
}

DirectX::XMFLOAT2 Mouse::GetPosition()
{
	return DirectX::XMFLOAT2(m_xPosition, m_yPosition);
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
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::EnterWindow, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::OnMouseLeaveWindow()
{
	m_isInWindow = false;
	m_eventBuffer.push(MouseEvent(MouseEvent::EventType::LeaveWindow, m_isLeftPressed, m_isRightPressed, m_xPosition, m_yPosition));
	TrimBuffer();
}

void Mouse::TrimBuffer()
{
	while (m_eventBuffer.size() > m_bufferSize)
	{
		m_eventBuffer.pop();
	}
}