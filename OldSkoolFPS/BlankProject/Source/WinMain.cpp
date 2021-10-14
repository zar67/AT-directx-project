#include "pch.h"

WCHAR		WindowClassName[MAX_NAME_STRING];
WCHAR		WindowTitle[MAX_NAME_STRING];

INT			WindowWidth;
INT			WindowHeight;

HICON		hIcon;

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) // Params: Window Instance, Message, Message Arguments, ??
{
	switch (message)
	{
		case WM_DESTROY: // Recieved at the end of a close window request.
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWnd, message, wparam, lparam);
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	/* Initialize Global Variables */

	LoadString(HInstance(), IDS_WINDOWCLASSNAME, WindowClassName, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_GAMENAME, WindowTitle, MAX_NAME_STRING);

	WindowWidth = 1366;
	WindowHeight = 768;

	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));

	/* Create Window Class */

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // The size of the class (initialises).
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Want a horizontal and vertical redraw.
	wcex.cbClsExtra = 0; // Used to add extra memory at run time.
	wcex.cbWndExtra = 0; // Used to add extra memory at run time.

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Set to default cursor.
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Set background to while (NULL_BRUSH).

	// Set program icon to custom application icon.
	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;

	wcex.lpszClassName = WindowClassName; // Set the window's class name.
	wcex.lpszMenuName = nullptr; // No need for a menu in a game.

	wcex.hInstance = HInstance(); // Set the program instance.

	wcex.lpfnWndProc = WindowProcess; // Custom Window Process.

	RegisterClassEx(&wcex);

	/* Create the Window */

	HWND hWnd = CreateWindow(WindowClassName, WindowTitle, WS_OVERLAPPEDWINDOW, // Params: Class, Title, Window Style
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr); // Params: X, Y, Width, Height, Parent, Menu, Instance, ??

	if (!hWnd) // If the window hasn't been created properly, don't continue and show an error.
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		return 0;
	}

	/* Show the Window */
	ShowWindow(hWnd, SW_SHOW); // Params: Window Handle, Bool to Show Window

	/* Listen for Message Events */

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		// If there are any messages then process them.
		// PeekMessage is a non-blocking command so we can run other code while checking for messages.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}