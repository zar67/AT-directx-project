/* ------------------------------------------------- */
/* Filename: Game.h                                  */
/* Author: Zoe Rowbotham                             */
/* Description: Header file for the Game class.      */
/* The Game class handles the update loop of the     */
/* game and hold any data about the game.            */
/* ------------------------------------------------- */

#pragma once
#include "Window.h"
#include "RotatingBox.h"
#include "Timer.h"

class Game
{
public:
	Game();
	int Run();
private:
	void Init();
	void Update(float deltaTime);
	void Render();

	Window m_window;
	Timer m_timer;

	std::unique_ptr<RotatingBox> m_box;
};