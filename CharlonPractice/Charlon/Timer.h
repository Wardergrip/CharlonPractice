#pragma once

// Credits to Jonas Samyn
// https://github.com/samynjonas

class Timer final
{
public:
	Timer(float timeGoal = 0);

	void Update(float elapsedSec);

	void SetTimeGoal(float seconds);
	void ResetTimer();
	float GetTime() const;
	const float& GetTimeRef() const;
	float GetPercentageDone() const;

	bool IsDone() const;

private:
	float m_TimeGoal;
	float m_AccumulateSeconds;

	bool m_IsTimerDone;
};

