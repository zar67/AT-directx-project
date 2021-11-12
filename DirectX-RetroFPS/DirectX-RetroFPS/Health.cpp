#include "Health.h"

#include <algorithm>

void Health::SetMaxHealth(float max)
{
	m_maxHealth = max;
}

void Health::Reset()
{
	m_currentHealth = m_maxHealth;
}

void Health::Damage(float damage)
{
	m_currentHealth -= damage;
}

void Health::Heal(float amount)
{
	m_currentHealth += amount;
	m_currentHealth = std::min(m_maxHealth, m_currentHealth);
}

bool Health::IsDead()
{
	return m_currentHealth <= 0;
}

bool Health::IsAtMaxHealth()
{
	return m_currentHealth == m_maxHealth;
}

float Health::GetMaxHealth()
{
	return m_maxHealth;
}

float Health::GetCurrentHealth()
{
	return m_currentHealth;
}
