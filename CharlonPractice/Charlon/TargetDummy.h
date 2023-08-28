#pragma once
#include "Unit.h"

class InfoPlate;
class Timer;
class SmartTextComponent;
class Chronometer;

class TargetDummy final : public Unit
{
public:
	TargetDummy(const Point2f& position = {});
	TargetDummy(const TargetDummy& unit) = delete;
	TargetDummy& operator=(const TargetDummy& unit) = delete;
	TargetDummy(TargetDummy&& unit) = delete;
	TargetDummy& operator=(TargetDummy&& unit) = delete;
	~TargetDummy();

	void Draw() const override;
	void Update(float elapsedSec) override;

	bool TakeDamage(float damageAmount) override;
private:
	InfoPlate* m_pInfoPlate;
	Timer* m_pTimer;

	float m_TotalDmgTaken;
	Chronometer* m_pDpsChrono;
	SmartTextComponent* m_pLastHitText;
	SmartTextComponent* m_pDpsText;
};

