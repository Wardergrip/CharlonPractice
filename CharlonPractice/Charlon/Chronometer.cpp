#include "pch.h"
#include "Chronometer.h"

Chronometer::Chronometer(bool start)
	:m_TotalElapsedSec{0}
	,m_IsCounting{start}
{
}

void Chronometer::Update(float elapsedSec)
{
	if (m_IsCounting)
	{
		m_TotalElapsedSec += elapsedSec;
	}
}

float Chronometer::GetTime() const
{
	return m_TotalElapsedSec;
}

const float& Chronometer::GetTimeRef() const
{
	return m_TotalElapsedSec;
}

bool Chronometer::IsCounting() const
{
	return m_IsCounting;
}

void Chronometer::ResetTime()
{
	m_TotalElapsedSec = 0;
}

void Chronometer::ResetAndStop()
{
	ResetTime();
	Stop();
}

void Chronometer::Start()
{
	m_IsCounting = true;
}

void Chronometer::Stop()
{
	m_IsCounting = false;
}

void Chronometer::SwitchStartStop()
{
	m_IsCounting = !m_IsCounting;
}
