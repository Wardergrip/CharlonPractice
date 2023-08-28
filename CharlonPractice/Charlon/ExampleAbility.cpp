#include "pch.h"
#include "ExampleAbility.h"

#include <iostream>
#include "utils.h"

#include "Timer.h"

#include "ProjectileManager.h"

ExampleAbility::ExampleAbility(const std::string& key, const Point2f& championLocationRef)
	:Ability(Type::skillshot,key,"ExampleAbility",3,10)
	,m_ChampionLocationRef{championLocationRef}
	,m_IsHoldingDown{false}
	,m_LastMousePos{}
	,m_Range{200}
{
}

ExampleAbility::~ExampleAbility()
{
}

void ExampleAbility::Draw() const
{
	if (m_IsHoldingDown)
	{
		Vector2f direction{m_LastMousePos - m_ChampionLocationRef};
		direction = direction.Normalized();
		Point2f point{ m_ChampionLocationRef + direction * m_Range };
		utils::SetColor(Color4f{0,1,1,1});
		utils::DrawLine(m_ChampionLocationRef, point);
	}
}

bool ExampleAbility::OnPress(const Point2f& mousePos)
{
	if (m_IsHoldingDown)
	{

	}
	else
	{
		m_IsHoldingDown = true;
	}
	return false;
}

bool ExampleAbility::OnHolding(float elapsedSec, const Point2f& mousePos)
{
	m_LastMousePos = mousePos;
	return false;
}

bool ExampleAbility::OnRelease(const Point2f& mousePos)
{
	m_IsHoldingDown = false;
	if (m_Cooldown->IsDone())
	{
		Vector2f direction{ m_LastMousePos - m_ChampionLocationRef };
		direction = direction.Normalized();
		Point2f point{ m_ChampionLocationRef + direction * m_Range };
		c_ProjectileManagerRef->PushBackSkillShot(m_ChampionLocationRef, point,20,100);
		m_Cooldown->ResetTimer();
		return true;
	}
	return false;
}

void ExampleAbility::Update(float elapsedSec)
{
	m_Cooldown->Update(elapsedSec);
}

void ExampleAbility::DrawIcon() const
{
	
}
