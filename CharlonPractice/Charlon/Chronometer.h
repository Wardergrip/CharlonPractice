#pragma once
class Chronometer final
{
public:
	Chronometer(bool start = false);
	Chronometer(const Chronometer& other) = default;
	Chronometer& operator=(const Chronometer& other) = default;
	Chronometer(Chronometer&& other) = default;
	Chronometer& operator=(Chronometer&& other) = default;
	~Chronometer() = default;

	void Update(float elapsedSec);

	float GetTime() const;
	const float& GetTimeRef() const;
	bool IsCounting() const;

	void ResetTime();
	void ResetAndStop();
	void Start();
	void Stop();
	void SwitchStartStop();

private:
	float m_TotalElapsedSec;
	bool m_IsCounting;
};

