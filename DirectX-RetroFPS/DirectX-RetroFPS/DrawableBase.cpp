#include "DrawableBase.h"

void DrawableBase::Draw(Graphics& graphics)
{
	if (!m_isActive)
	{
		return;
	}

	for (auto& b : m_bindables)
	{
		b->Bind(graphics);
	}

	for (auto& b : GetStaticBinds())
	{
		b->Bind(graphics);
	}

	graphics.GetDeviceContext()->DrawIndexed(m_pIndexBuffer->GetCount(), 0u, 0u);
}

void DrawableBase::Update(float deltaTime)
{

}

void DrawableBase::OnCollision(CollisionUtilities::ColliderCollision collision, DrawableBase* other)
{

}

void DrawableBase::OnShot(DrawableBase* shooter, float damage, Vector shotContactPosition)
{

}

void DrawableBase::AddBindable(std::unique_ptr<Bindable> bindable)
{
	m_bindables.push_back(std::move(bindable));
}

Transform& DrawableBase::GetTransform()
{
	return m_transform;
}

OBBCollider& DrawableBase::GetCollider()
{
	return m_collider;
}

bool DrawableBase::IsActive()
{
	return m_isActive;
}

void DrawableBase::SetActive(bool value)
{
	m_isActive = value;
}