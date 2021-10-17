#include "Timer.h"

Timer::Timer() noexcept
{
	m_lastTimePoint = std::chrono::steady_clock::now();
}

float Timer::Mark() noexcept
{
	const auto old = m_lastTimePoint;
	m_lastTimePoint = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frameTime = m_lastTimePoint - old;
	return frameTime.count();
}

float Timer::Peek() const noexcept
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - m_lastTimePoint).count();
}
