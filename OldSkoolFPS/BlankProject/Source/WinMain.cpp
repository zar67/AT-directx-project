/* ------------------------------------------------- */
/* Filename: WinMain.cpp                             */
/* Author: Zoe Rowbotham                             */
/* Description: Main entry file for the program,     */
/* initialises the window and important things...    */
/* ------------------------------------------------- */

#include <Windows.h>
#include "../Window.h"
#include "../resource.h"
#include "../Game.h"

// CALLBACK: Tells C++ to use __stdcall instead of the usual calling method.
// This function hasn't changed since Windows 3.1.
// hInstance: The instance of the program and can always be found through GetModuleHandle(NULL).
// hPrevInstance: The previous instance and will always return null - it's no longer used.
// lpCmdLine: The command line input string.
// nCmdShow: Bitflag to indicate how the window should be shown on startup.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	return Game{}.Run();
}