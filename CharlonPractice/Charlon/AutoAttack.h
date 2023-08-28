#pragma once
#include "LockOnProjectile.h"
class AutoAttack : public LockOnProjectile
{
public:
	AutoAttack(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	AutoAttack(const AutoAttack& autoAttack) = delete;
	AutoAttack& operator=(const AutoAttack& autoAttack) = delete;
	AutoAttack(AutoAttack&& autoAttack) = delete;
	AutoAttack& operator=(AutoAttack&& autoAttack) = delete;
	virtual ~AutoAttack();

	// Returns a copy of the autoattack
	virtual AutoAttack* Clone() const;
	// Returns an autoattack with the same damage and speed
	virtual AutoAttack* Clone(const Point2f& startingPos, Unit* target) const;

private:
};

