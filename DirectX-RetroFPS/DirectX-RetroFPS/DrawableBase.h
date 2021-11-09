#pragma once

#include <memory>

#include "Graphics.h"
#include "Bindable.h"
#include "IndexBuffer.h"
#include "CollisionUtilities.h"

class DrawableBase
{
public:
	DrawableBase() = default;
	virtual ~DrawableBase() = default;

	virtual void Draw(Graphics& graphics);
	virtual void Update(float deltaTime);
	virtual void OnCollision(CollisionUtilities::CollisionData collision);

	void AddBindable(std::unique_ptr<Bindable> bindable);

	Transform& GetTransform();
	Collider& GetCollider();
    
	bool IsActive();
	void SetActive(bool value);

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


protected:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const = 0;

	IndexBuffer* m_pIndexBuffer = nullptr;
	Transform m_transform;
	Collider m_collider;
	std::vector<std::unique_ptr<Bindable>> m_bindables;

	bool m_isActive = true;
};