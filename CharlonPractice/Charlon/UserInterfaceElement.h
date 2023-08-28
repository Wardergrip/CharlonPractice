#pragma once

#include "Transform.h"

class UserInterfaceElement
{
public:
	UserInterfaceElement(const Rectf& rect);
	UserInterfaceElement(const UserInterfaceElement& other) = delete;
	UserInterfaceElement& operator=(const UserInterfaceElement& other) = delete;
	UserInterfaceElement(UserInterfaceElement&& other) = delete;
	UserInterfaceElement& operator=(UserInterfaceElement&& other) = delete;
	virtual ~UserInterfaceElement();

	virtual void Draw() const;

	void SetRect(const Rectf& rect);
	void SetBL(const Point2f& bottomLeft);

	void CenterTo(const Point2f& center);

	Point2f GetCenter() const;
	bool IsInside(const Point2f& pos) const;

	Point2f CenterOf() const;

	bool GetAutomaticHUDDraw() const;
	void ChangeAutomaticHUDDraw(bool state);

protected:
	Transform m_Transform;
	Rectf m_Rect;
	bool m_AutomaticHUDDraw;
};

