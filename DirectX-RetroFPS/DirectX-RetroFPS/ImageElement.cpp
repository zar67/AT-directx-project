#include "ImageElement.h"

#include "TextureBindable.h"

ImageElement::ImageElement(Graphics& graphics, std::string imageFilename) : UIElement(graphics)
{
	std::unique_ptr<TextureBindable> texture = std::make_unique<TextureBindable>(graphics, imageFilename);
	AddBindable(std::move(texture));
}