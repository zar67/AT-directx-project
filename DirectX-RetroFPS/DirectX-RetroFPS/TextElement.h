#pragma once

#include "UIElement.h"
#include "TextBindable.h"

class TextElement : public UIElement
{
public:
	TextElement(Graphics& graphics, std::string fontFilename);
	virtual ~TextElement() = default;

	void Draw(Graphics& graphics) override;
	void Update(float deltaTime) override;

	void SetText(std::string text);
	void SetTransform(Transform& transform);
	void SetColour(float r, float g, float b, float a);

private:
	TextBindable* m_pTextBindable = nullptr;
};