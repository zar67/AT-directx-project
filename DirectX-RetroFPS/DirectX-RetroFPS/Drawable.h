#pragma once
#include "DrawableBase.h"

template<class T>
class Drawable : public DrawableBase
{
public:
	Drawable() = default;
protected:
	static bool IsStaticInitialized() 
	{
		return !m_staticBindables.empty();
	}

	static void AddStaticBindable(std::unique_ptr<Bindable> bindable) 
	{
		m_staticBindables.push_back(std::move(bindable));
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