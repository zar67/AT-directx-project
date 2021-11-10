#define NOMINMAX

#include "Shooter.h"

void Shooter::SetDamage(float damage)
{
	m_damage = damage;
}

void Shooter::SetParent(DrawableBase* drawable)
{
	m_pParent = drawable;
}

void Shooter::StartShoot(Ray ray)
{
	m_shootRay = ray;
	m_nearestCollision = CollisionUtilities::RayCollision();
	m_nearestCollision.IntersectionDistance = std::numeric_limits<float>().max();
	m_nearestCollisionDrawable = nullptr;
}

void Shooter::RegisterCollision(CollisionUtilities::RayCollision collision, DrawableBase* drawable)
{
	if (collision.IntersectionDistance < m_nearestCollision.IntersectionDistance)
	{
		m_nearestCollision = collision;
		m_nearestCollisionDrawable = drawable;
	}
}

void Shooter::HandleHit()
{
	if (m_nearestCollisionDrawable != nullptr)
	{
		m_nearestCollisionDrawable->OnShot(m_pParent, m_damage, m_nearestCollision.IntersectionPosition);
	}
}

Ray& Shooter::GetShootRay()
{
	return m_shootRay;
}