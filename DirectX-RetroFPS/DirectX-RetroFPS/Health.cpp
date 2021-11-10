#include "Health.h"

void Health::SetMaxHealth(float max)
{
	m_maxHealth = max;
}

void Health::Reset()
{
	m_currentHealth = m_maxHealth;
}

bool Health::IsDead()
{
	return m_currentHealth <= 0;
}

void Health::Damage(float damage)
{
	m_currentHealth -= damage;
}