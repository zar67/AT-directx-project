#include "Stat.h"

#include <algorithm>

void Stat::SetMaxValue(float max)
{
	m_maxValue = max;
}

void Stat::SetToMaxValue()
{
	m_currentValue = m_maxValue;
}

void Stat::Decrease(float damage)
{
	m_currentValue -= damage;
}

void Stat::Increase(float amount)
{
	m_currentValue += amount;
	m_currentValue = std::min(m_maxValue, m_currentValue);
}

bool Stat::IsZero()
{
	return m_currentValue <= 0;
}

float Stat::GetMaxValue()
{
	return m_maxValue;
}

float Stat::GetCurrentValue()
{
	return m_currentValue;
}
