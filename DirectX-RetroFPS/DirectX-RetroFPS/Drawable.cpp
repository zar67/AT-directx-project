/* ------------------------------------------------- */
/* Filename: Drawable.cpp                            */
/* Author: Zoe Rowbotham                             */
/* Description: Includes function declarations for   */
/* the Drawable class.                               */
/* ------------------------------------------------- */

#include "Drawable.h"
#include "IndexBuffer.h"

void Drawable::Draw(Graphics& graphics)
{
	for (auto& b : m_bindables)
	{
		b->Bind(graphics);
	}

	graphics.GetDeviceContext()->DrawIndexed(m_pIndexBuffer->GetCount(), 0u, 0u);
}

void Drawable::Update(float deltaTime)
{

}

void Drawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer)
{
	assert("Cannot add more than one IndexBuffer to Drawable" && m_pIndexBuffer == nullptr);
	m_pIndexBuffer = indexBuffer.get();
	m_bindables.push_back(std::move(indexBuffer));
}

void Drawable::AddBindable(std::unique_ptr<Bindable> bindable)
{
	assert("Must use AddIndexBuffer to add an IndexBuffer" && typeid(*bindable) != typeid(IndexBuffer));
	m_bindables.push_back(std::move(bindable));
}
