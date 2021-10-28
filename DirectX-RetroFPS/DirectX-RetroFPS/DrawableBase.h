#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include "IndexBuffer.h"
#include "Transform.h"

class DrawableBase
{
public:
	virtual ~DrawableBase() = default;

	virtual void Draw(Graphics& graphics);
	virtual void Update(float deltaTime);

	void AddIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);
	void AddBindable(std::unique_ptr<Bindable> bindable);

	Transform* GetTransform();

protected:
	IndexBuffer* m_pIndexBuffer = nullptr;
	Transform m_transform;
	std::vector<std::unique_ptr<Bindable>> m_bindables;
};