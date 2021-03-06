#define NOMINMAX

#include "Shooter.h"

void Shooter::SetParent(DrawableBase* drawable)
{
	m_pParent = drawable;
}

void Shooter::StartShoot(Ray ray)
{
	ClearShooter();
	m_shootRay = ray;
	m_pWeapon->Fired();
}

void Shooter::ClearShooter()
{
	m_shootRay = Ray();
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
	if (m_nearestCollisionDrawable != nullptr && m_nearestCollision.IntersectionDistance <= m_pWeapon->GetRange())
	{
		m_nearestCollisionDrawable->OnShot(m_pParent, m_pWeapon->GetDamage(), m_nearestCollision.IntersectionPosition);
	}
}

bool Shooter::CanShoot()
{
	return m_pWeapon->CanFire();
}

bool Shooter::IsShooting()
{
	return m_shootRay.IsValid();
}

Ray& Shooter::GetShootRay()
{
	return m_shootRay;
}

Weapon* Shooter::GetWeapon()
{
	return m_pWeapon;
}

void Shooter::SetWeapon(Weapon* weapon)
{
	m_pWeapon = weapon;
}