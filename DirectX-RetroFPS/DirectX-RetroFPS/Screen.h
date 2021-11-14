#pragma once

#include <vector>

#include "ScreenType.h"
#include "UIElement.h"
#include "Input.h"

class Screen
{
public:
	Screen() = default;
	virtual ~Screen() = default;

	void AddElement(std::unique_ptr<UIElement> drawable, Camera* targetCamera);
	
	virtual ScreenType HandleInput(Input& input);
	void Update(float deltaTime);
	void Draw(Graphics& graphics);

protected:
	ScreenType m_screenType;
	std::vector<std::unique_ptr<UIElement>> m_elements;
};