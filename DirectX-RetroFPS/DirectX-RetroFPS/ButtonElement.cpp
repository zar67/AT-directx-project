#include "ButtonElement.h"

ButtonElement::ButtonElement(Graphics& graphics, std::string imageFilename) : UIElement(graphics)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, imageFilename, 1, 2);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));

	m_isSelected = false;
	UpdateImage();
}

void ButtonElement::Draw(Graphics& graphics)
{
	m_pVertexBuffer->Update(graphics, m_vertices);

	UIElement::Draw(graphics);
}

bool ButtonElement::IsSelected()
{
	return m_isSelected;
}

void ButtonElement::Select()
{
	m_isSelected = true;
	UpdateImage();
}

void ButtonElement::Deselect()
{
	m_isSelected = false;
	UpdateImage();
}

void ButtonElement::UpdateImage()
{
	if (m_isSelected)
	{
		m_pSpriteSheet->SetCoordsToSpriteAt(0, m_textureCoords);
	}
	else
	{
		m_pSpriteSheet->SetCoordsToSpriteAt(1, m_textureCoords);
	}

	for (int i = 0; i < 4; i++)
	{
		m_vertices[i].TextureCoords = m_textureCoords[i].Coordinate;
	}
}