#pragma once
#include "MouseEvent.h"
#include <queue>
#include <Windows.h>

class Mouse
{
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	void HandleMessages(UINT message, WPARAM wparam, LPARAM lparam);

	std::pair<int, int> GetPos();
	int GetXPos();
	int GetYPos();

	bool IsLeftPressed();
	bool IsRightPressed();

	MouseEvent Read();
	bool IsEventBufferEmpty();
	void Flush();

private:
	void OnMouseMove(int x, int y);

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

	void TrimBuffer();

	static constexpr unsigned int m_bufferSize = 16u;

	int m_xPosition;
	int m_yPosition;

	bool m_isLeftPressed = false;
	bool m_isLeftHeld = false;
	bool m_isRightPressed = false;
	bool m_isRightHeld = false;
	bool m_isMiddlePressed = false;
	bool m_isMiddleHeld = false;
	
	std::queue<MouseEvent> m_eventBuffer;
};