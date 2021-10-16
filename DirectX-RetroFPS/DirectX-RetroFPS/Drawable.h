/* ------------------------------------------------- */
/* Filename: Drawable.h                              */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Drawable class         */
/* ------------------------------------------------- */

#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include "IndexBuffer.h"

class Drawable
{
public:
	virtual ~Drawable() = default;

	void Draw(Graphics& graphics);
	virtual void Update(float deltaTime);

	void AddIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);
	void AddBindable(std::unique_ptr<Bindable> bindable);

protected:
	IndexBuffer* m_pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> m_bindables;
};