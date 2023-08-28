#include "pch.h"
#include "TargetDummy.h"

#include "InfoPlate.h"
#include "Timer.h"
#include "Chronometer.h"

#include "SmartTextComponent.h"

#include <iostream>

#include "utils.h"

TargetDummy::TargetDummy(const Point2f& position)
	:Unit(position,Rectf{0,0,30,30})
	,m_pInfoPlate{new InfoPlate(this)}
	,m_pTimer{new Timer{3}}
	,m_TotalDmgTaken{0}
	,m_pDpsChrono{new Chronometer(false)}
	,m_pLastHitText{new SmartTextComponent("Last hit: 0")}
	,m_pDpsText{new SmartTextComponent("DPS: 0")}
{
	m_pLastHitText->ChangeAutomaticHUDDraw(false);
	m_pDpsText->ChangeAutomaticHUDDraw(false);

	m_pLastHitText->ChangeTransform(Transform(Point2f{ position.x - 50, position.y - 40 }));
	m_pDpsText->ChangeTransform(Transform(Point2f{ position.x - 50, position.y - 60 }));

	m_pInfoPlate->SetName("Target Dummy");
	m_UnitColor = Color4f{ 209 / 255.f, 79 / 255.f, 15 / 255.f, 1.f };
}

TargetDummy::~TargetDummy()
{
	delete m_pTimer;
	m_pTimer = nullptr;
	delete m_pDpsChrono;
	m_pDpsChrono = nullptr;
}

void TargetDummy::Draw() const
{
	Unit::Draw();
	m_pInfoPlate->Draw();

	m_pLastHitText->Draw();
	m_pDpsText->Draw();
}

void TargetDummy::Update(float elapsedSec)
{
	m_pTimer->Update(elapsedSec);
	m_pDpsChrono->Update(elapsedSec);
	if ((int(m_pDpsChrono->GetTime() * 100.f) % 4) == 0)
	{
		if (m_pDpsChrono->GetTime() == 0)
		{
			m_pDpsText->UpdateText("DPS: " + std::to_string(0), true);
		}
		else
		{
			m_pDpsText->UpdateText("DPS: " + std::to_string(int(m_TotalDmgTaken / m_pDpsChrono->GetTime())), true);
		}
	}
	if (m_pTimer->IsDone())
	{
		m_BasicStats.currentHealth = m_BasicStats.maxHealth;
		m_TotalDmgTaken = 0;
		m_pDpsChrono->ResetAndStop();
		m_pDpsText->UpdateText("DPS: " + std::to_string(0), false);
		m_pLastHitText->UpdateText("Last hit: " + std::to_string(0), false);
	}
}

bool TargetDummy::TakeDamage(float damageAmount)
{
	m_pTimer->ResetTimer();
	m_pDpsChrono->Start();
	m_TotalDmgTaken += damageAmount;
	std::cout << "[TARGET DUMMY] " << damageAmount << " damage taken! Health left: " << m_BasicStats.currentHealth - damageAmount << '\n';
	m_pLastHitText->UpdateText("Last hit: " + std::to_string(int(damageAmount)),false);
	return Unit::TakeDamage(damageAmount);
}
