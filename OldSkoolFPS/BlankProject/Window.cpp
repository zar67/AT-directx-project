#include <stdexcept>
#include "Window.h"

Window::Window(int width, int height, const int name, const int icon)
{
	hInst = GetModuleHandle(nullptr);

	LoadString(hInst, IDS_WINDOWCLASSNAME, wndClassName, MAX_NAME_STRING);
	LoadString(hInst, name, wndTitle, MAX_NAME_STRING);
	hIcon = LoadIcon(hInst, MAKEINTRESOURCE(icon));

	wndWidth = width;
	wndHeight = height;

	CreateWindowClass();
	InitialiseWindow();
}

Window::~Window()
{
	UnregisterClass(wndClassName, hInst);
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg;

	// If there are any messages then process them.
	// PeekMessage is a non-blocking command so we can run other code while checking for messages.
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

Graphics& Window::GetGraphics()
{
	return *m_pGraphics;
}

LRESULT Window::HandleMessageSetup(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_NCCREATE) // Sent when a window is first created.
	{
		// Due to the 'this' in the CreateWindow function, lparam is the Window class 
		// instance we need to subscribe the HandleMessage function to.
		// We cannot directly subscribe a member function to lpfnWndProc, so we use a
		// static function instead.

		// Get the actual Window instance pointer.
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCT*>(lparam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		// Store the window instance pointer to the WinAPI-managed user data.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		// Set the windows process to the HandleMessageThunk now we are setup correctly. 
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));

		return pWnd->HandleMessage(hWnd, message, wparam, lparam);
	}

	return DefWindowProc(hWnd, message, wparam, lparam);
}

LRESULT Window::HandleMessageThunk(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	// Get the window instance pointer we stored to the user data in setup.
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// Call the HandleMessage function on the Window instance.
	return pWnd->HandleMessage(hWnd, message, wparam, lparam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
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

void Window::CreateWindowClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // The size of the structure (initialises).
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Want a horizontal and vertical redraw.
	wcex.cbClsExtra = 0; // Used to add extra memory at run time.
	wcex.cbWndExtra = 0; // Used to add extra memory at run time.
	wcex.hInstance = hInst;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Set to default cursor.
	wcex.hbrBackground = nullptr;

	// Set program icon to custom application icon.
	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;

	wcex.lpszClassName = wndClassName; // Set the window's class name.
	wcex.lpszMenuName = nullptr; // No need for a menu in a game.

	wcex.hInstance = hInst; // Set the program instance.

	wcex.lpfnWndProc = HandleMessageSetup; // Custom Window Process for behaviour and look of the window.

	RegisterClassEx(&wcex);
}

void Window::InitialiseWindow()
{
	INT offset = 100;

	RECT wndRect;
	wndRect.left = offset;
	wndRect.right = wndWidth + offset;
	wndRect.top = offset;
	wndRect.bottom = wndHeight + offset;

	AdjustWindowRect(&wndRect, WS_OVERLAPPEDWINDOW, FALSE);

	/* Create the Window */
	HWND hWnd = CreateWindowEx(
		0, wndClassName, wndTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, wndWidth, wndHeight,
		nullptr, nullptr, hInst, this
	);

	if (!hWnd) // If the window hasn't been created properly, don't continue and show an error.
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		PostQuitMessage(0);
	}

	/* Show the Window */
	ShowWindow(hWnd, SW_SHOW); // Params: Window Handle, Bitflag to Show Window.

	m_pGraphics = std::make_unique<Graphics>(hWnd);
}