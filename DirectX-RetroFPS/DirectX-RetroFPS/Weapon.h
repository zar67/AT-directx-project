#pragma once

#include "WeaponType.h"

class Weapon
{
public:
	Weapon(WeaponType type, float damage, int defaultBullets, float reloadDelay, bool infiniteBullets);
	~Weapon() = default;

	void AddBullets(int amount);
	int GetBullets();

	float GetDamage();

	void Update(float deltaTime);

	void Fired();
	bool CanFire();

private:
	WeaponType m_weaponType;

	float m_damage;

	bool m_infiniteBullets;
	int m_bullets;

	float m_reloadDelay;
	float m_reloadTimer;
};