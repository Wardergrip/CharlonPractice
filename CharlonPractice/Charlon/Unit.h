#pragma once
#include "Transform.h"
#include <vector>

#include "BasicStats.h"

class Unit
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
	Unit(const Point2f& position = {}, const Rectf& hitbox = {});
	Unit(const Rectf& hitbox);
	Unit(const Unit& unit) = delete;
	Unit& operator=(const Unit& unit) = delete;
	Unit(Unit&& unit) = delete;
	Unit& operator=(Unit&& unit) = delete;
	virtual ~Unit() = default;

	virtual void Draw() const;
	virtual void Update(float elapsedSec);

	virtual void OnMouseDown(const SDL_MouseButtonEvent& e);
	virtual void OnMouseUp(const SDL_MouseButtonEvent& e);
	virtual void OnMouseMotion(const SDL_MouseMotionEvent& e);

	virtual void OnKeyDown(const SDL_KeyboardEvent& e, const Point2f& mousePos) ;
	virtual void OnKeyHold(float elapsedSec, const Uint8* pStates, const Point2f& mousePos);
	virtual void OnKeyUp(const SDL_KeyboardEvent& e, const Point2f& mousePos) ;

	bool IsOverlapping(const Point2f& point) const;
	bool IsOverlapping(const Rectf& rect) const;
	bool IsOverlapping(const Circlef& circle) const;
	bool IsOverlapping(const Unit& unit) const;

	// Locacation = point and hitbox middle will be point
	void CenterTo(const Point2f& point = {});
	// Hitbox middle will be the transform.location
	void CenterHitboxToPosition();
	void TeleportTo(const Point2f& location);
	void RotateTowards(const Point2f& target);
	void StopMovement();

	const Transform& GetTransform() const;
	void GetTransform(Transform& output) const;

	const BasicStats& GetBasicStats() const;
	// Returns if the Unit is still in positive health amount
	virtual bool TakeDamage(float damageAmount);
	// Returns if it succeeded
	virtual bool TakeMana(int manaAmount);
	
	Rectf GetHitbox() const;

protected:
	Rectf m_Hitbox;
	Transform m_Transform;
	Point2f m_Destination;
	BasicStats m_BasicStats;
	bool m_IsHoldingRightClick;
	Color4f m_UnitColor;

	void DrawHitbox() const;

	void MoveTowards(const Point2f& point, float elapsedSec);

	void OnMouseDownBasic(const SDL_MouseButtonEvent& e);
	void OnMouseUpBasic(const SDL_MouseButtonEvent& e);
	void OnMouseMotionBasic(const SDL_MouseMotionEvent& e);

};

