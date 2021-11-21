#pragma once

#include <queue>
#include <Windows.h>

#include "MouseEvent.h"
#include <optional>

class Mouse
{
public:
	struct RawDelta
	{
		int X;
		int Y;
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	void HandleMessages(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, int windowWidth, int windowHeight);
	void DetectHeldButtons();

	bool IsInWindow();

	int GetXPos();
	int GetYPos();

	MouseEvent::ButtonState GetLeftButtonState();
	MouseEvent::ButtonState GetRightButtonState();
	MouseEvent::ButtonState GetMiddleButtonState();

	bool IsLeftButtonDown();
	bool IsRightButtonDown();
	bool IsMiddleButtonDown();

	std::optional<RawDelta> ReadRawDelta();

	MouseEvent Read();
	bool IsEventBufferEmpty();
	void Flush();

private:
	void OnMouseMove(int x, int y);
	void OnRawDelta(int dx, int dy);

	void OnLeftPressed(int x, int y);
	void OnLeftHeld(int x, int y);
	void OnLeftReleased(int x, int y);

	void OnRightPressed(int x, int y);
	void OnRightHeld(int x, int y);
	void OnRightReleased(int x, int y);

	void OnMiddlePressed(int x, int y);
	void OnMiddleHeld(int x, int y);
	void OnMiddleReleased(int x, int y);

	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);
	void OnWheelDelta(int x, int y, int delta);

	void OnMouseEnterWindow();
	void OnMouseLeaveWindow();

	void TrimBuffer();

	static constexpr unsigned int m_bufferSize = 16u;

	bool m_isInWindow = false;

	MouseEvent::ButtonState m_leftButtonState = MouseEvent::ButtonState::NOT_PRESSED;
	MouseEvent::ButtonState m_rightButtonState = MouseEvent::ButtonState::NOT_PRESSED;
	MouseEvent::ButtonState m_middleButtonState = MouseEvent::ButtonState::NOT_PRESSED;

	int m_xPosition;
	int m_yPosition;

	int m_wheelDeltaCarry = 0;
	
	std::queue<MouseEvent> m_eventBuffer;

	std::queue<RawDelta> m_rawDeltaBuffer;
	std::vector<BYTE> m_rawBuffer;
};