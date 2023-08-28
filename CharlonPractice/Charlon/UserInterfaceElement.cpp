#include "pch.h"
#include "UserInterfaceElement.h"

#include "utils.h"
using namespace utils;

#include "HUD.h"

#include <iostream>

UserInterfaceElement::UserInterfaceElement(const Rectf& rect)
	:m_Transform{ Point2f{rect.left,rect.bottom} }
	,m_Rect{rect}
	,m_AutomaticHUDDraw{true}
{
	m_Rect.left = 0;
	m_Rect.bottom = 0;

	HUD::QueueUI(std::pair<HUD::HUDName, UserInterfaceElement*>{HUD::HUDName::ingame, this});
}

UserInterfaceElement::~UserInterfaceElement()
{
}

void UserInterfaceElement::Draw() const
{
	m_Transform.Push();
	{
		m_Transform.Apply();
		FillRect(m_Rect);
	}
	m_Transform.Pop();
}

void UserInterfaceElement::SetRect(const Rectf& rect)
{
	m_Rect.width = rect.width;
	m_Rect.height = rect.height;
	m_Transform.location.x = m_Rect.left;
	m_Transform.location.y = m_Rect.bottom;
}

void UserInterfaceElement::SetBL(const Point2f& bottomLeft)
{
	m_Transform.location.x = bottomLeft.x;
	m_Transform.location.y = bottomLeft.y;
}

void UserInterfaceElement::CenterTo(const Point2f& p)
{
	m_Transform.location = p;
	m_Rect = Rectf(- (m_Rect.width / 2), - (m_Rect.height / 2), m_Rect.width, m_Rect.height);
}

Point2f UserInterfaceElement::GetCenter() const
{
	return Point2f(m_Transform.location.x + m_Rect.width / 2, m_Transform.location.y + m_Rect.height / 2);
}

bool UserInterfaceElement::IsInside(const Point2f& pos) const
{
	return IsPointInRect(pos, Rectf{m_Transform.location.x,m_Transform.location.y,m_Rect.width,m_Rect.height});
}

Point2f UserInterfaceElement::CenterOf() const
{
	return Point2f(m_Transform.location.x + m_Rect.width / 2, m_Transform.location.y + m_Rect.height / 2);
}

bool UserInterfaceElement::GetAutomaticHUDDraw() const
{
	return m_AutomaticHUDDraw;
}

void UserInterfaceElement::ChangeAutomaticHUDDraw(bool state)
{
	m_AutomaticHUDDraw = state;
}
