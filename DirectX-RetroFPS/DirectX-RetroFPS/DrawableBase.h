#pragma once

#include <memory>
#include <typeindex>

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

	void AddBindable(std::unique_ptr<Bindable> bindable);

	template<class B>
	B* GetBindableOfType()
	{
		for (auto& bindable : m_bindables)
		{
			B* castBind = dynamic_cast<B*>(bindable.get());
			if (castBind != nullptr)
			{
				return castBind;
			}
		}

		for (auto& bindable : GetStaticBinds())
		{
			B* castBind = dynamic_cast<B*>(bindable.get());
			if (castBind != nullptr)
			{
				return castBind;
			}
		}

		return nullptr;
	}

	Transform* GetTransform();

protected:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;

	IndexBuffer* m_pIndexBuffer = nullptr;
	Transform m_transform;
	std::vector<std::unique_ptr<Bindable>> m_bindables;
};