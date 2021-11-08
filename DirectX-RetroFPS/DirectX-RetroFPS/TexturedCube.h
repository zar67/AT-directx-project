#pragma once
#include "Drawable.h"

class TexturedCube : public Drawable<TexturedCube>
{
public:
	TexturedCube() = default;
	TexturedCube(Graphics& graphics);

private:
	void InitialiseStatic(Graphics& graphics);
	void InitialiseCollider();
};