#include "TextElement.h"

TextElement::TextElement(Graphics& graphics, std::string fontFilename) : UIElement(graphics)
{
	std::unique_ptr<TextBindable> textBindable = std::make_unique<TextBindable>(graphics, fontFilename);
	textBindable->SetTransform(m_transform);

	m_pTextBindable = textBindable.get();
	AddBindable(std::move(textBindable));
}

void TextElement::Draw(Graphics& graphics)
{
	m_pTextBindable->Draw(graphics);
}

void TextElement::Update(float deltaTime)
{
}

void TextElement::SetText(std::string text)
{
	m_pTextBindable->SetText(text);
}

void TextElement::SetTransform(Transform& transform)
{
	m_pTextBindable->SetTransform(transform);
}

void TextElement::SetColour(float r, float g, float b, float a)
{
	m_pTextBindable->SetColour(r, g, b, a);
}