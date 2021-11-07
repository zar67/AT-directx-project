#include "Animation.h"

Animation::Animation(SpriteSheet* pSpriteSheet, std::vector<int> spriteIndexes, float playbackSpeed)
{
	m_pSpriteSheet = pSpriteSheet;
	m_playbackSpeed = playbackSpeed;
	m_spriteIndexes = spriteIndexes;
}

void Animation::Update(float deltaTime, std::vector<DirectX::XMFLOAT2>& textureCoords)
{
	m_animationTimer += deltaTime;
	while (m_animationTimer >= 1 / m_playbackSpeed)
	{
		ChangeSprite(textureCoords);
		m_animationTimer -= 1 / m_playbackSpeed;
	}
}

void Animation::ChangeSprite(std::vector<DirectX::XMFLOAT2>& textureCoords)
{
	SpriteSheet::SpriteBounds currentSpriteRect = m_pSpriteSheet->GetSpriteBoundsAtIndex(m_spriteIndexes[m_currentSpriteIndex]);

	m_currentSpriteIndex++;
	m_currentSpriteIndex %= m_spriteIndexes.size();

	SpriteSheet::SpriteBounds newSpriteRect = m_pSpriteSheet->GetSpriteBoundsAtIndex(m_spriteIndexes[m_currentSpriteIndex]);

	float xOffset = newSpriteRect.Left - currentSpriteRect.Left;
	float yOffset = newSpriteRect.Top - currentSpriteRect.Top;

	for (auto& vertex : textureCoords)
	{
		vertex.x += xOffset;
		vertex.y += yOffset;
	}
}