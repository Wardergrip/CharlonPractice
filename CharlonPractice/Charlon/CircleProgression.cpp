#include "pch.h"
#include "CircleProgression.h"

#include "Timer.h"

#include "utils.h"
using namespace utils;

// STATICS

void CircleProgression::DrawCircleProgression(const Point2f& location, float radX, float radY, float percentage, bool isFilled)
{
	float fromAngle{float(M_PI) / 2};
	float tillAngle{float(2 * M_PI) * percentage + float(M_PI) / 2};
	if (isFilled)
	{
		
		FillArc(location, radX, radY, fromAngle,tillAngle);
	}
	else 
	{
		DrawArc(location, radX, radY, fromAngle, tillAngle);
	}
}

// NON STATICS

CircleProgression::CircleProgression(const Point2f& location, const float& percentage, bool isFilled)
	:m_Transform{location}
	,m_pPercentage{percentage}
	,m_IsFilled{isFilled}
	,m_Percentage{}
	,m_RadX{10}
	,m_RadY{10}
	,m_TimerRef{nullptr}
{
}

CircleProgression::CircleProgression(const Point2f& location, const Timer& timer, bool isFilled)
	:CircleProgression(location,isFilled)
{
	m_TimerRef = &timer;
}

CircleProgression::CircleProgression(const Point2f& location, bool isFilled)
	:CircleProgression(location,m_Percentage,isFilled)
{
}

void CircleProgression::Draw() const
{
	m_Transform.Push();
	{
		m_Transform.Apply();
		if (m_TimerRef)
		{
			DrawCircleProgression(Point2f{}, m_RadX, m_RadY, m_TimerRef->GetPercentageDone(), m_IsFilled);
		}
		else
		{
			DrawCircleProgression(Point2f{}, m_RadX, m_RadY, m_pPercentage, m_IsFilled);
		}
	}
	m_Transform.Pop();
}

void CircleProgression::SetPercentage(float percentage)
{
	m_Percentage = percentage;
}

void CircleProgression::SetIsFilled(bool isFilled)
{
	m_IsFilled = isFilled;
}

void CircleProgression::SetLocation(const Point2f& location)
{
	m_Transform.location;
}

void CircleProgression::SetScale(const Vector2f& scale)
{
	m_Transform.scale = scale;
}

void CircleProgression::SetRotation(float angle)
{
	m_Transform.angle = angle;
}

void CircleProgression::SetRadX(float radX)
{
	if (radX <= 0) return;
	m_RadX = radX;
}

void CircleProgression::SetRadY(float radY)
{
	if (radY <= 0) return;
	m_RadY = radY;
}

void CircleProgression::SetRad(float radX, float radY)
{
	if (radY == -1.f)
	{
		radY = radX;
	}
	SetRadX(radX);
	SetRadY(radY);
}

void CircleProgression::FlipY()
{
	m_Transform.FlipY();
}

void CircleProgression::FlipX()
{
	m_Transform.FlipX();
}
