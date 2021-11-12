#include "AnimatedImageElement.h"

AnimatedImageElement::AnimatedImageElement(Graphics& graphics, std::string imageFilename, int columnCount, int rowCount) : UIElement(graphics)
{
	std::unique_ptr<SpriteSheet> spriteSheet = std::make_unique<SpriteSheet>(graphics, imageFilename, columnCount, rowCount);
	m_pSpriteSheet = spriteSheet.get();
	AddBindable(std::move(spriteSheet));
}

void AnimatedImageElement::Draw(Graphics& graphics)
{
	m_pVertexBuffer->Update(graphics, m_vertices);

	UIElement::Draw(graphics);
}

void AnimatedImageElement::ChangeSprite(int index)
{
	m_pSpriteSheet->SetCoordsToSpriteAt(index, m_textureCoords);

	for (int i = 0; i < 4; i++)
	{
		m_vertices[i].TextureCoords = m_textureCoords[i].Coordinate;
	}
}