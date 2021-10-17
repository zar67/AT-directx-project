#pragma once
#include "DrawableBase.h"

template<class T>
class Drawable : public DrawableBase
{
protected:
	static bool IsStaticInitialized() 
	{
		return !m_staticBindables.empty();
	}

	static void AddStaticBindable(std::unique_ptr<Bindable> bindable) 
	{
		assert("Must use AddStaticIndexBuffer to bind IndexBuffer" && typeid(*bindable) != typeid(IndexBuffer));
		m_staticBindables.push_back(std::move(bindable));
	}

	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer)
	{
		assert("Cannot add move than one IndexBuffer" && m_pIndexBuffer == nullptr);
		m_pIndexBuffer = indexBuffer.get();
		m_staticBindables.push_back(std::move(indexBuffer));
	}

	void SetIndexFromStatic()
	{
		assert("Cannot add move than one IndexBuffer" && m_pIndexBuffer == nullptr);
		for (const auto& b : m_staticBindables)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{
				m_pIndexBuffer = p;
				return;
			}
		}
		assert("Failed to find IndexBuffer in static binds" && m_pIndexBuffer != nullptr);
	}

	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const override
	{
		return m_staticBindables;
	}
private:
	static std::vector<std::unique_ptr<Bindable>> m_staticBindables;
};

template<class T>
std::vector<std::unique_ptr<Bindable>> Drawable<T>::m_staticBindables;