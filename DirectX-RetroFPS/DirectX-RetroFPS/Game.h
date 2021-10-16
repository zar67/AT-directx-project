/* ------------------------------------------------- */
/* Filename: Game.h                                  */
/* Author: Zoe Rowbotham                             */
/* Description: Header file for the Game class.      */
/* The Game class handles the update loop of the     */
/* game and hold any data about the game.            */
/* ------------------------------------------------- */

#pragma once
#include "Window.h"
#include "Box.h"

class Game
{
public:
	Game();
	int Run();
private:
	void Init();
	void Update();
	void Render();

	Window m_window;
	std::unique_ptr<Box> m_box;
};