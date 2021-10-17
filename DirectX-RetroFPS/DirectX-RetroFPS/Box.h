#pragma once
#include "Drawable.h"

class Box : public Drawable<Box>
{
public:
	Box() = default;
	Box(Graphics& graphics);
private:
	void InitialiseStatic(Graphics& graphics);
};