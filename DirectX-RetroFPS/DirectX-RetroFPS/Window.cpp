#include <stdexcept>
#include "Window.h"
#include "ErrorLogger.h"

Window::Window(int width, int height, const int name, const int icon)
{
	m_instance = GetModuleHandle(nullptr);

	LoadString(m_instance, IDS_WINDOWCLASSNAME, m_windowClassName, MAX_WINDOW_NAME_STRING);
	LoadString(m_instance, name, m_windowTitle, MAX_WINDOW_NAME_STRING);
	m_icon = LoadIcon(m_instance, MAKEINTRESOURCE(icon));

	m_windowWidth = width;
	m_windowHeight = height;

	CreateWindowClass();
	InitialiseWindow(width, height);
}

Window::~Window()
{
	UnregisterClass(m_windowClassName, m_instance);
}

std::optional<int> Window::ProcessWindowsMessages()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

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

Input& Window::GetInput()
{
	return *m_pInput;
}

LRESULT Window::HandleMessageSetup(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_NCCREATE) // Sent when a window is first created.
	{
		// We cannot directly subscribe a member function to lpfnWndProc, so we use a
		// static function instead, get the instance, then call the member function.

		// Due to the 'this' in the CreateWindow function, lparam is the Window class 
		// instance we need to subscribe the HandleMessage function to.

		// Get the actual Window instance pointer.
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCT*>(lparam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		// Store the window instance pointer to the WinAPI-managed user data.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		// Set the windows process to the HandleMessageThunk now we are setup correctly. 
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageBridge));

		return pWnd->HandleMessage(hWnd, message, wparam, lparam);
	}

	return DefWindowProc(hWnd, message, wparam, lparam);
}

LRESULT Window::HandleMessageBridge(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	// Get the window instance pointer we stored to the user data in HandleMessageSetup.
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// Call the HandleMessage function on the Window instance.
	return pWnd->HandleMessage(hWnd, message, wparam, lparam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);

			// If we don't do this, DefWindowProc will destroy the window twice.
			return 0;
		}
		default:
		{
			m_pInput->HandleMessages(hWnd, message, wparam, lparam);
		}
	}

	// Still need to call the Default Window Process to handle any messages we don't.
	return DefWindowProc(hWnd, message, wparam, lparam);
}

void Window::CreateWindowClass()
{
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(WNDCLASSEX); // The size of the structure (initialises).
	windowClass.style = CS_HREDRAW | CS_VREDRAW; // Want a horizontal and vertical redraw.
	windowClass.cbClsExtra = 0; // Used to add extra memory at run time.
	windowClass.cbWndExtra = 0; // Used to add extra memory at run time.
	windowClass.hInstance = m_instance;

	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = nullptr;

	// Set program icon to custom application icon.
	windowClass.hIcon = m_icon;
	windowClass.hIconSm = m_icon;

	windowClass.lpszClassName = m_windowClassName; // Set the window's class name.
	windowClass.lpszMenuName = nullptr; // No need for a menu in a game.

	windowClass.hInstance = m_instance;

	windowClass.lpfnWndProc = HandleMessageSetup; // Custom Window Process for behaviour and look of the window.

	RegisterClassEx(&windowClass);
}

void Window::InitialiseWindow(int width, int height)
{
	int screenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	int screenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	RECT windowRect;
	windowRect.left = screenCenterX;
	windowRect.right = m_windowWidth + windowRect.left;
	windowRect.top = screenCenterY;
	windowRect.bottom = m_windowHeight + windowRect.top;

	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	// Create the Window
	HWND window = CreateWindowEx(
		0, m_windowClassName, m_windowTitle, WS_OVERLAPPEDWINDOW,
		windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		nullptr, nullptr, m_instance, this
	);

	if (!window) // If the window hasn't been created properly, don't continue and show an error.
	{
		ErrorLogger::Log(GetLastError(), "InitialiseWindow Failed");
		PostQuitMessage(0);
	}

	// Show the Window
	ShowWindow(window, SW_SHOW);

	// Initialise the graphics.
	m_pGraphics = std::make_unique<Graphics>(window, width, height);

	m_pInput = std::make_unique<Input>();
}