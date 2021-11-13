#pragma once

#include "UIElement.h"

#include "SpriteSheet.h"

class AnimatedImageElement : public UIElement
{
public:
	AnimatedImageElement(Graphics& graphics, std::string imageFilename, int columnCount, int rowCount);
	virtual ~AnimatedImageElement() = default;

	void Draw(Graphics& graphics) override;
	void ChangeSprite(int index);

private:
	SpriteSheet* m_pSpriteSheet = nullptr;
};