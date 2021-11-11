#include "UIManager.h"
#include "MainMenuScreen.h"
#include "GameHUDScreen.h"
#include "GameOverScreen.h"

UIManager::UIManager(Graphics& graphics)
{
	m_screens[ScreenType::MAIN_MENU] = std::make_unique<MainMenuScreen>(graphics);
	m_screens[ScreenType::GAME_HUD] = std::make_unique<GameHUDScreen>(graphics);
	m_screens[ScreenType::GAME_OVER] = std::make_unique<GameOverScreen>(graphics);
}

void UIManager::HandleInput(Input& input)
{
	m_currentScreen = m_screens[m_currentScreen]->HandleInput(input);
}

void UIManager::Update(float deltaTime)
{
	m_screens[m_currentScreen]->Update(deltaTime);
}

void UIManager::Draw(Graphics& graphics)
{
	m_screens[m_currentScreen]->Draw(graphics);
}

void UIManager::GoToScreen(ScreenType screen)
{
	m_currentScreen = screen;
}

ScreenType UIManager::GetCurrentScreenID()
{
	return m_currentScreen;
}