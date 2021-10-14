#pragma once
#include <Windows.h>
#include <optional>
#include <memory>
#include "resource.h"
#include "Graphics.h"

#define MAX_NAME_STRING 256

class Window
{
public:
	Window(int width, int height, const int name, const int icon);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	static std::optional<int> ProcessMessages();

	Graphics& GetGraphics();

private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	void CreateWindowClass();
	void InitialiseWindow();

	std::unique_ptr<Graphics> m_pGraphics;

	WCHAR wndClassName[MAX_NAME_STRING];
	WCHAR wndTitle[MAX_NAME_STRING];
	HICON hIcon;
	HINSTANCE hInst;

	INT wndWidth;
	INT wndHeight;
};