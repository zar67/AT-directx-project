#include "UIManager.h"
#include "MainMenuScreen.h"

UIManager::UIManager(Graphics& graphics)
{
	m_screens[ScreenID::MAIN_MENU] = std::make_unique<MainMenuScreen>(graphics);
	m_screens[ScreenID::GAME_HUD] = std::make_unique<Screen>();
	m_screens[ScreenID::GAME_OVER] = std::make_unique<Screen>();
}

void UIManager::Update(float deltaTime)
{
	m_screens[m_currentScreen]->Update(deltaTime);
}

void UIManager::Draw(Graphics& graphics)
{
	m_screens[m_currentScreen]->Draw(graphics);
}

void UIManager::GoToScreen(ScreenID screen)
{
	m_currentScreen = screen;
}

UIManager::ScreenID UIManager::GetCurrentScreenID()
{
	return m_currentScreen;
}