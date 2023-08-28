#include "pch.h"
#include "AutoAttack.h"

AutoAttack::AutoAttack(const Point2f& startingPos, Unit* target, float damage, float speed)
	:LockOnProjectile(startingPos,target,damage,speed)
{
}

AutoAttack::~AutoAttack()
{
}

AutoAttack* AutoAttack::Clone() const
{
	return Clone(m_Transform.location, m_pTarget);
}

AutoAttack* AutoAttack::Clone(const Point2f& startingPos, Unit* target) const
{
	return new AutoAttack(startingPos,target,m_Damage,m_Speed);
}
