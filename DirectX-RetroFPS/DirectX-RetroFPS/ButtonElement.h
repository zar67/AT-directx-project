#pragma once

#include "UIElement.h"
#include "SpriteSheet.h"

class ButtonElement : public UIElement
{
public:
	ButtonElement(Graphics& graphics, std::string imageFilename);
	virtual ~ButtonElement() = default;

	virtual void Draw(Graphics& graphics) override;

	bool IsSelected();

	void Select();
	void Deselect();

private:
	void UpdateImage();

	SpriteSheet* m_pSpriteSheet = nullptr;
	bool m_isSelected = false;
};