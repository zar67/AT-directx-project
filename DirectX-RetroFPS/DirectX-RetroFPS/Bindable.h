#pragma once

#include "Graphics.h"

class Bindable
{
public:
	Bindable() = default;
	virtual ~Bindable() = default;

	virtual void Bind(Graphics& graphics);
};