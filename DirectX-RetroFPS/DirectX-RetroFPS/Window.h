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
	Window(int width, int height, const int name, const int icon);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	static std::optional<int> ProcessWindowsMessages();

	Graphics& GetGraphics();
	Input& GetInput();

	int GetWidth();
	int GetHeight();

private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK HandleMessageBridge(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	void CreateWindowClass();
	void InitialiseWindow(int width, int height);

	std::unique_ptr<Graphics> m_pGraphics;
	std::unique_ptr<Input> m_pInput;

	WCHAR m_windowClassName[MAX_WINDOW_NAME_STRING];
	WCHAR m_windowTitle[MAX_WINDOW_NAME_STRING];
	HICON m_icon;
	HINSTANCE m_instance;

	int m_windowWidth;
	int m_windowHeight;
};