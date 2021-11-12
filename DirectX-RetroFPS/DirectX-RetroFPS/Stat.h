#pragma once

class Stat
{
public:
	Stat() = default;

	void SetMaxValue(float max);

	void SetToMaxValue();
	void Decrease(float damage);
	void Increase(float amount);

	bool IsZero();

	float GetMaxValue();
	float GetCurrentValue();

private:
	float m_maxValue = 0;
	float m_currentValue = 0;
};