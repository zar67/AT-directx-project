#pragma once
#include "Graphics.h"

class Bindable
{
public:
	Bindable() = default;
	virtual ~Bindable() = default;

	Bindable(const Bindable&) = default;
	Bindable& operator=(const Bindable&) = default;

	virtual void Bind(Graphics& graphics);
};