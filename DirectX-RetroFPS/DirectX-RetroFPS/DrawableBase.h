/* ------------------------------------------------- */
/* Filename: Drawable.h                              */
/* Author: Zoe Rowbotham                             */
/* Description: Header of the Drawable class         */
/* ------------------------------------------------- */

#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include "IndexBuffer.h"

class DrawableBase
{
public:
	virtual ~DrawableBase() = default;

	void Draw(Graphics& graphics);
	virtual void Update(float deltaTime);

	void AddIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);
	void AddBindable(std::unique_ptr<Bindable> bindable);

protected:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;

	IndexBuffer* m_pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> m_bindables;
};