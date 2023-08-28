#include "pch.h"
#include "Timer.h"

Timer::Timer(float timeGoal)
	: m_TimeGoal{ timeGoal }
	, m_AccumulateSeconds{ 0.f }
	, m_IsTimerDone{ false }
{
}

void Timer::Update(float elapsedSec)
{
	if (m_IsTimerDone == false)
	{
		m_AccumulateSeconds += elapsedSec;
		if (m_AccumulateSeconds >= m_TimeGoal)
		{
			m_IsTimerDone = true;
		}
	}
}

void Timer::SetTimeGoal(float seconds)
{
	m_TimeGoal = seconds;
}

void Timer::ResetTimer()
{
	m_AccumulateSeconds = 0;
	m_IsTimerDone = false;
}

bool Timer::IsDone() const
{
	return m_IsTimerDone;
}

float Timer::GetTime() const
{
	return m_AccumulateSeconds;
}

const float& Timer::GetTimeRef() const
{
	return m_AccumulateSeconds;
}

float Timer::GetPercentageDone() const
{
	if (m_IsTimerDone)
	{
		return 1.00f;
	}
	return (m_AccumulateSeconds / m_TimeGoal);
}
