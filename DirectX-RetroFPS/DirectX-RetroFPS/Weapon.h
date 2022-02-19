#pragma once

#include "WeaponType.h"

class Weapon
{
public:
	Weapon(WeaponType type, float damage, int defaultBullets, float reloadDelay, float range, bool hasInfiniteBullets);
	~Weapon() = default;

	void AddBullets(int amount);
	int GetBullets();

	float GetDamage();
	float GetRange();

	void Update(float deltaTime);

	void Fired();
	bool CanFire();
	bool ShowShootImage();
	WeaponType GetType();

private:
	WeaponType m_weaponType;

	float m_damage;
	float m_range;

	bool m_hasInfiniteBullets;
	int m_bullets;

	float m_reloadDelay;
	float m_reloadTimer;

	float m_shootImageDelay = 0.1f;
};