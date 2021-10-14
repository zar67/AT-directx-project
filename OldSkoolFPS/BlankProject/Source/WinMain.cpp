#include <windows.h>

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

WCHAR		WindowClassName[MAX_NAME_STRING];
WCHAR		WindowTitle[MAX_NAME_STRING];

INT			WindowWidth;
INT			WindowHeight;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	/* Initialize Global Variables */

	wcscpy_s(WindowClassName, TEXT("OldSkoolFPS"));
	wcscpy_s(WindowTitle, TEXT("Doom But Better"));

	WindowWidth = 1366;
	WindowHeight = 768;

	/* Create Window Class */

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); // The size of the class (initialises).
	wcex.style = CS_HREDRAW | CS_VREDRAW; // Want a horizontal and vertical redraw.
	wcex.cbClsExtra = 0; // Used to add extra memory at run time.
	wcex.cbWndExtra = 0; // Used to add extra memory at run time.

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // Set to default cursor.
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH); // Set background to while (NULL_BRUSH).

	// Set program icon to default application icon.
	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);

	wcex.lpszClassName = WindowClassName;
	wcex.lpszMenuName = nullptr;

	wcex.hInstance = HInstance();
	wcex.lpfnWndProc = DefWindowProc; // Default Windows Process.

	RegisterClassEx(&wcex);

	/* Create the Window */

	HWND hWnd = CreateWindow(WindowClassName, WindowTitle, WS_OVERLAPPEDWINDOW, // Class, Title, Window Style
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr); // X, Y, Width, Height, Parent, Menu, Instance, ??

	if (!hWnd) // If the window hasn't been created properly, don't continue and show an error.
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		return 0;
	}

	/* Show the Window */
	ShowWindow(hWnd, SW_SHOW); // Window Handle, Bool to Show Window

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