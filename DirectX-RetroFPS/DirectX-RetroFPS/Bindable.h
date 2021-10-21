/* ------------------------------------------------- */
/* Filename: Bindable.h                              */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Bindable class.        */
/* A base class for any that needs to be binded to   */
/* the graphics pipeline in order to render to the   */
/* screen. E.g. InputLayout, PixelShader etc.        */
/* ------------------------------------------------- */

#pragma once
#include "Graphics.h"

class Bindable
{
public:
	Bindable() = default;
	virtual ~Bindable() = default;

	virtual void Bind(Graphics& graphics);
};