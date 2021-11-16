#include "Weapon.h"
#include "SoundManager.h"

Weapon::Weapon(WeaponType type, float damage, int defaultBullets, float reloadDelay, float range, bool infiniteBullets)
{
	m_weaponType = type;
	m_damage = damage;
	m_range = range;
	m_bullets = defaultBullets;
	m_reloadDelay = reloadDelay;
	m_hasInfiniteBullets = infiniteBullets;
	m_reloadTimer = 0;
}

void Weapon::AddBullets(int amount)
{
	if (m_bullets + amount <= 9999)
	{
		m_bullets += amount;
	}
	else
	{
		m_bullets = 9999;
	}
}

int Weapon::GetBullets()
{
	return m_bullets;
}

float Weapon::GetDamage()
{
	return m_damage;
}

float Weapon::GetRange()
{
	return m_range;
}

void Weapon::Update(float deltaTime)
{
	m_reloadTimer += deltaTime;
}

void Weapon::Fired()
{
	m_reloadTimer = 0;

	if (!m_hasInfiniteBullets)
	{
		m_bullets--;
	}

	switch (m_weaponType)
	{
		case WeaponType::FIST:
		{
			SoundManager::Play(SoundType::FIST_FIRE);
			break;
		}
		case WeaponType::CHAINSAW:
		{
			SoundManager::Play(SoundType::CHAINSAW_FIRE);
			break;
		}
		case WeaponType::PISTOL:
		{
			SoundManager::Play(SoundType::PISTOL_FIRE);
			break;
		}
		case WeaponType::RIFLE:
		{
			SoundManager::Play(SoundType::RIFLE_FIRE);
			break;
		}
		case WeaponType::SHOTGUN:
		{
			SoundManager::Play(SoundType::SHOTGUN_FIRE);
			break;
		}
		case WeaponType::CANNON:
		{
			SoundManager::Play(SoundType::CANNON_FIRE);
			break;
		}
	}
}

bool Weapon::CanFire()
{
	return m_reloadTimer >= m_reloadDelay && (m_bullets > 0 || m_hasInfiniteBullets);
}

bool Weapon::ShowShootImage()
{
	return m_reloadTimer <= m_shootImageDelay;
}

WeaponType Weapon::GetType()
{
	return m_weaponType;
}