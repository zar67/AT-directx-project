#pragma once

#include <Windows.h>
#include <optional>
#include <memory>

#include "resource.h"
#include "Graphics.h"
#include "Input.h"

#define MAX_WINDOW_NAME_STRING 256

class Window
{
public:
	Window();
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	static std::optional<int> ProcessWindowsMessages();

	Graphics& GetGraphics();
	Input& GetInput();

	void ShowCursor();
	void HideCursor();

private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK HandleMessageBridge(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	void CreateWindowClass();
	void InitialiseWindow();

	std::unique_ptr<Graphics> m_pGraphics;
	std::unique_ptr<Input> m_pInput;

	HWND m_window;
	WCHAR m_windowClassName[MAX_WINDOW_NAME_STRING];
	WCHAR m_windowTitle[MAX_WINDOW_NAME_STRING];
	HICON m_icon;
	HINSTANCE m_instance;

	bool m_isCursorEnabled = true;
};