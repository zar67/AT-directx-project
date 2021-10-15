/* ------------------------------------------------- */
/* Filename: WinMain.cpp                             */
/* Author: Zoe Rowbotham                             */
/* Description: Main entry file for the program,     */
/* creates a Game and sets it running.               */
/* ------------------------------------------------- */

#include <Windows.h>
#include "../Window.h"
#include "../resource.h"
#include "../Game.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	return Game{}.Run();
}