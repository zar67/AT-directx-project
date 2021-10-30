#include <Windows.h>

#include "Game.h"

int main(int argc, char* argv[])
{
	return Game{}.Run();
}

//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
//{
//	return Game{}.Run();
//}