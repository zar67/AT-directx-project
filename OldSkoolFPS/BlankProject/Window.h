#pragma once
#include <Windows.h>
#include "resource.h"

#define MAX_NAME_STRING 256

class Window
{
public:
	Window(int width, int height, const int name, const int icon);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

	VOID CreateWindowClass();
	VOID InitialiseWindow();
	VOID HandleWindowsMessages();

	WCHAR wndClassName[MAX_NAME_STRING];
	WCHAR wndTitle[MAX_NAME_STRING];
	HICON hIcon;
	HINSTANCE hInst;

	INT wndWidth;
	INT wndHeight;
};