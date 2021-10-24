#pragma once
#include "Drawable.h"

class SolidCube : public Drawable<SolidCube>
{
public:
	SolidCube() = default;
	SolidCube(Graphics& graphics);
private:
	void InitialiseStatic(Graphics& graphics);
};