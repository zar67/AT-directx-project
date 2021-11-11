#pragma once

#include "UIElement.h"

class ImageElement : public UIElement
{
public:
	ImageElement(Graphics& graphics, std::string imageFilename);
};