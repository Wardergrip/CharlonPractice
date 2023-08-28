#pragma once

#include "Transform.h"

class Unit;

class LockOnProjectile
{
// STATICS
public:
	static void SetDrawingHitboxes(bool state);
	static void SwitchDrawingHitboxes();
	static bool IsDrawingHitboxes();
protected:
	static bool c_IsDrawingHitboxes;

// NON STATICS
public:
	LockOnProjectile(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	LockOnProjectile(const LockOnProjectile& proj) = delete;
	LockOnProjectile& operator=(const LockOnProjectile& proj) = delete;
	LockOnProjectile(LockOnProjectile&& proj) = delete;
	LockOnProjectile& operator=(LockOnProjectile&& proj) = delete;
	virtual ~LockOnProjectile();

	virtual void Draw() const;
	virtual void Update(float elapsedSec);

	virtual bool HasHit() const;

protected:
	Transform m_Transform;
	float m_Speed;
	float m_Damage;
	Unit* m_pTarget;
	Rectf m_Hitbox;

	bool m_HasHit;
};

