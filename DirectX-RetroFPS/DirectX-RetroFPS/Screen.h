#pragma once

#include <vector>

#include "UIElement.h"

class Screen
{
public:
	Screen() = default;
	~Screen() = default;

	void AddElement(std::unique_ptr<UIElement> drawable, Camera* targetCamera);
	
	void Update(float deltaTime);
	void Draw(Graphics& graphics);

private:
	std::vector<std::unique_ptr<UIElement>> m_elements;
};

