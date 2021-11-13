#include "Screen.h"

void Screen::AddElement(std::unique_ptr<UIElement> drawable, Camera* targetCamera)
{
	drawable->SetTargetCamera(targetCamera);
	m_elements.push_back(std::move(drawable));
}

ScreenType Screen::HandleInput(Input& input)
{
	return m_screenType;
}

void Screen::Update(float deltaTime)
{
	for (auto& element : m_elements)
	{
		element->Update(deltaTime);
	}
}

void Screen::Draw(Graphics& graphics)
{
	for (auto& element : m_elements)
	{
		element->Draw(graphics);
	}
}