#pragma once

#include <memory>

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
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;

	IndexBuffer* m_pIndexBuffer = nullptr;
	Transform m_transform;
	std::vector<std::unique_ptr<Bindable>> m_bindables;
};