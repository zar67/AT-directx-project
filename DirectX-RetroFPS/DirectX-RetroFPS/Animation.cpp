#include "Animation.h"
#include <iostream>

Animation::Animation(SpriteSheet* pSpriteSheet, std::vector<int> spriteIndexes, float playbackSpeed)
{
	m_pSpriteSheet = pSpriteSheet;
	m_playbackSpeed = playbackSpeed;

	m_spriteIndexes = spriteIndexes;
}

void Animation::Update(float deltaTime, std::vector<TextureCoordinate>& textureCoords)
{
	m_animationTimer += deltaTime;
	while (m_animationTimer >= 1 / m_playbackSpeed)
	{
		ChangeSprite(textureCoords);
		m_animationTimer -= 1 / m_playbackSpeed;
	}
}

int Animation::GetStartingSpriteIndex()
{
	return m_spriteIndexes[0];
}

void Animation::ChangeSprite(std::vector<TextureCoordinate>& textureCoords)
{
	SpriteSheet::SpriteBounds currentSpriteRect = m_pSpriteSheet->GetSpriteBoundsAtIndex(m_spriteIndexes[m_currentSpriteIndex]);

	m_currentSpriteIndex++;
	m_currentSpriteIndex %= m_spriteIndexes.size();

	SpriteSheet::SpriteBounds newSpriteRect = m_pSpriteSheet->GetSpriteBoundsAtIndex(m_spriteIndexes[m_currentSpriteIndex]);

	for (auto& vertex : textureCoords)
	{
		switch (vertex.Position)
		{
			case TextureCoordinate::Position::TOP_LEFT:
			{
				vertex.Coordinate.x = newSpriteRect.Left;
				vertex.Coordinate.y = newSpriteRect.Top;
				break;
			}
			case TextureCoordinate::Position::TOP_RIGHT:
			{
				vertex.Coordinate.x = newSpriteRect.Right;
				vertex.Coordinate.y = newSpriteRect.Top;
				break;
			}
			case TextureCoordinate::Position::BOTTOM_LEFT:
			{
				vertex.Coordinate.x = newSpriteRect.Left;
				vertex.Coordinate.y = newSpriteRect.Bottom;
				break;
			}
			case TextureCoordinate::Position::BOTTOM_RIGHT:
			{
				vertex.Coordinate.x = newSpriteRect.Right;
				vertex.Coordinate.y = newSpriteRect.Bottom;
				break;
			}
		}
	}
}