#include "Input.h"
#include "ErrorLogger.h"

Input::Input()
{
	RAWINPUTDEVICE rawInputDevice;
	rawInputDevice.usUsagePage = 0x01;
	rawInputDevice.usUsage = 0x02;
	rawInputDevice.dwFlags = 0;
	rawInputDevice.hwndTarget = nullptr;

	if (RegisterRawInputDevices(&rawInputDevice, 1, sizeof(rawInputDevice)) == FALSE)
	{
		ErrorLogger::Log(GetLastError(), "Registering Raw Input Devices Failed.");
	}
}

void Input::HandleMessages(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, int windowWidth, int windowHeight)
{
	m_keyboard.HandleMessages(message, wparam, lparam);
	m_mouse.HandleMessages(hWnd, message, wparam, lparam, windowWidth, windowHeight);
}

void Input::UpdateStates()
{
	m_mouse.DetectHeldButtons();
	m_keyboard.DetectedHeldKeys();
}

Keyboard& Input::GetKeyboard()
{
	return m_keyboard;
}

Mouse& Input::GetMouse()
{
	return m_mouse;
}
