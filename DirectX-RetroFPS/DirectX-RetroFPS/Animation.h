#pragma once

#include <vector>

#include "SpriteSheet.h"
#include "TextureCoordinate.h"

class Animation
{
public:
	Animation() = default;
	Animation(SpriteSheet* pSpriteSheet, std::vector<int> spriteIndexes, float playbackSpeed);

	void Update(float deltaTime, std::vector<TextureCoordinate>& textureCoords);
	void Reset();
	void Reset(int frame, float animationTimer);

	int GetStartingSpriteIndex();
	bool Completed();

	int GetCurrentSpriteIndex();
	float GetCurrentAnimationTimer();

private:
	void ChangeSprite(std::vector<TextureCoordinate>& textureCoords);

	std::vector<int> m_spriteIndexes = {};

	SpriteSheet* m_pSpriteSheet = nullptr;

	float m_playbackSpeed = 0;
	float m_animationTimer = 0;

	int m_currentSpriteIndex = 0;
	int m_previousSpriteIndex = -1;
};