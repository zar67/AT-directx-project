/* ------------------------------------------------- */
/* Filename: WinMain.cpp                             */
/* Author: Zoe Rowbotham                             */
/* Description: Main entry file for the program,     */
/* initialises the window and important things...    */
/* ------------------------------------------------- */
#include "pch.h"

#pragma region GlobalVariables
/* ------------------------------------------------- */
/* Global Variables                                  */
/* ------------------------------------------------- */

WCHAR		WindowClassName[MAX_NAME_STRING];
WCHAR		WindowTitle[MAX_NAME_STRING];

INT			WindowWidth;
INT			WindowHeight;

HICON		hIcon;

/* ------------------------------------------------- */
#pragma endregion

#pragma region Pre-Declarations
/* ------------------------------------------------- */
/* Pre-Declarations                                  */
/* ------------------------------------------------- */

VOID InitialiseGlobalVariables();
VOID CreateWindowClass();
VOID InitialiseWindow();
VOID HandleWindowsMessages();
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

/* ------------------------------------------------- */
#pragma endregion

#pragma region Operations
/* ------------------------------------------------- */
/* Operations                                        */
/* ------------------------------------------------- */

// CALLBACK: Tells C++ to use __stdcall instead of the usual calling method.
// This function hasn't changed since Windows 3.1.
// hInstance: The instance of the program and can always be found through GetModuleHandle(NULL).
// hPrevInstance: The previous instance and will always return null - it's no longer used.
// lpCmdLine: The command line input string.
// nCmdShow: Bitflag to indicate how the window should be shown on startup.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	InitialiseGlobalVariables();
	CreateWindowClass();
	InitialiseWindow();
	HandleWindowsMessages();

	// Returns an exit code.
	return 0;
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) // Params: Window Instance, Message, Message Arguments, ??
{
	switch (message)
	{
	case WM_DESTROY: // Recieved at the end of a close window request.
		PostQuitMessage(0);
		break;
	}

	// Still need to call the Default Window Process to handle any messages we don't need to.
	return DefWindowProc(hWnd, message, wparam, lparam);
}
/* ------------------------------------------------- */
#pragma endregion

#pragma region Functions
/* ------------------------------------------------- */
/* Functions                                         */
/* ------------------------------------------------- */

VOID InitialiseGlobalVariables()
{
	/* Initialize Global Variables */
	LoadString(HInstance(), IDS_WINDOWCLASSNAME, WindowClassName, MAX_NAME_STRING);
	LoadString(HInstance(), IDS_GAMENAME, WindowTitle, MAX_NAME_STRING);

	WindowWidth = 1366;
	WindowHeight = 768;

	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
}

// The windows class defines lots of the information about the window.
// Once you have a windows class you can create one of more instances of the class.
// This is not done through C++ classes, this is done through the Windows API.
VOID CreateWindowClass()
{
	// EX means extended (it's the newer version).
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // The size of the structure (initialises).
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Want a horizontal and vertical redraw.
	wcex.cbClsExtra = 0; // Used to add extra memory at run time.
	wcex.cbWndExtra = 0; // Used to add extra memory at run time.

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Set to default cursor.
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Set background to white (NULL_BRUSH).

	// Set program icon to custom application icon.
	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;

	wcex.lpszClassName = WindowClassName; // Set the window's class name.
	wcex.lpszMenuName = nullptr; // No need for a menu in a game.

	wcex.hInstance = HInstance(); // Set the program instance.

	wcex.lpfnWndProc = WindowProcess; // Custom Window Process for behaviour and look of the window.

	RegisterClassEx(&wcex);
}

VOID InitialiseWindow()
{
	/* Create the Window */
	HWND hWnd = CreateWindowEx(
		0,						// Extended Window Style
		WindowClassName,		// Window Class Name
		WindowTitle,			// Window Title
		WS_OVERLAPPEDWINDOW,	// Window Style
		CW_USEDEFAULT,			// X
		0,						// Y
		WindowWidth,			// Width
		WindowHeight,			// Height
		nullptr,				// Parent Window
		nullptr,				// Menu
		HInstance(),			// Instance
		nullptr					// Message for Created Window
	);

	if (!hWnd) // If the window hasn't been created properly, don't continue and show an error.
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		PostQuitMessage(0);
	}

	/* Show the Window */
	ShowWindow(hWnd, SW_SHOW); // Params: Window Handle, Bitflag to Show Window.
}

VOID HandleWindowsMessages()
{
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
}

/* ------------------------------------------------- */
#pragma endregion