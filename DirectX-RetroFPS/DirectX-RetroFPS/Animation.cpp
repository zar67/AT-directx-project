#include "Animation.h"

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

void Animation::Reset()
{
	m_animationTimer = 0;

	m_currentSpriteIndex = 0;
	m_previousSpriteIndex = -1;
}

void Animation::Reset(int frame, float animationTimer)
{
	m_animationTimer = animationTimer;

	m_currentSpriteIndex = frame;
	m_previousSpriteIndex = frame - 1;
}

int Animation::GetStartingSpriteIndex()
{
	return m_spriteIndexes[0];
}

bool Animation::Completed()
{
	return m_currentSpriteIndex == 0 && m_previousSpriteIndex == m_spriteIndexes.size() - 1;
}

int Animation::GetCurrentSpriteIndex()
{
	return m_currentSpriteIndex;
}

float Animation::GetCurrentAnimationTimer()
{
	return m_animationTimer;
}

void Animation::ChangeSprite(std::vector<TextureCoordinate>& textureCoords)
{
	m_previousSpriteIndex = m_currentSpriteIndex;

	SpriteSheet::SpriteBounds currentSpriteRect = m_pSpriteSheet->GetSpriteBoundsAtIndex(m_spriteIndexes[m_currentSpriteIndex]);

	m_currentSpriteIndex++;
	m_currentSpriteIndex %= m_spriteIndexes.size();

	m_pSpriteSheet->SetCoordsToSpriteAt(m_spriteIndexes[m_currentSpriteIndex], textureCoords);
}