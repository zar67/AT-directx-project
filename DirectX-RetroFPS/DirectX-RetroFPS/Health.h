#pragma once

class Health
{
public:
	Health() = default;

	void SetMaxHealth(float max);

	void Reset();
	bool IsDead();
	void Damage(float damage);

private:
	float m_maxHealth;
	float m_currentHealth;
};