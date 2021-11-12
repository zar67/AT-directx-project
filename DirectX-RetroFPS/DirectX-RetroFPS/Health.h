#pragma once

class Health
{
public:
	Health() = default;

	void SetMaxHealth(float max);

	void Reset();
	void Damage(float damage);
	void Heal(float amount);

	bool IsDead();
	bool IsAtMaxHealth();

	float GetMaxHealth();
	float GetCurrentHealth();

private:
	float m_maxHealth;
	float m_currentHealth;
};