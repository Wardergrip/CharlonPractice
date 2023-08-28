#include "pch.h"
#include "Champion.h"

#include "utils.h"
#include "ExampleAbility.h"

#include "InfoPlate.h"

#include "Timer.h"

#include "ProjectileManager.h"

#include "OrientationManager.h"

#include "AutoAttack.h"

Champion::Champion(const Window& window, ProjectileManager* projectilemanagerref, const std::string& champName, bool defaultConfigure)
	:m_ProjectileManagerRef{ projectilemanagerref }
	,m_pAbilityInterface{new AbilityInterface(window,this)}
	,m_pInfoPlate{ new InfoPlate{ this } }
	,m_pAutoAttackTimer{ new Timer{1/2.f} }
	,m_pAutoAttack{nullptr}
	,m_AutoAttackRangeRadius{200.f}
	,m_DrawAARange{false}
{
	if (defaultConfigure)
	{
		m_pAbilityInterface->AssignAbility(AbilityKey::Q, new ExampleAbility("Q", this->m_Transform.location));
		m_pAutoAttack = new AutoAttack(m_Transform.location, nullptr);
	}
	m_Hitbox = Rectf{ 0,0,20,20 };
	CenterHitboxToPosition();

	m_pInfoPlate->SetName(champName);
}

Champion::~Champion()
{
	/*delete m_pAbilityInterface;
	m_pAbilityInterface = nullptr;*/
	delete m_pAutoAttackTimer;
	m_pAutoAttackTimer = nullptr;
	delete m_pAutoAttack;
	m_pAutoAttack = nullptr;
}

void Champion::Draw() const
{
	using namespace utils;

	m_Transform.Push();
	m_Transform.Apply();
	// Draw Unit
	DrawUnit();

	// Draw hitbox
	if (c_IsDrawingHitboxes)
	{
		DrawHitbox();
	}
	// Draw range
	if (m_DrawAARange)
	{
		DrawEllipse(Point2f{ 0,0 }, m_AutoAttackRangeRadius, m_AutoAttackRangeRadius);
	}
	m_Transform.Pop();

	m_pInfoPlate->Draw();
	m_pAbilityInterface->DrawAbilities();
}

void Champion::Update(float elapsedSec)
{
	m_pAbilityInterface->Update(elapsedSec);
	MoveTowards(m_Destination,elapsedSec);
	m_pAutoAttackTimer->Update(elapsedSec);
	m_BasicStats.RegenMana(elapsedSec);
}

void Champion::OnMouseDown(const SDL_MouseButtonEvent& e)
{
	OnMouseDownBasic(e);
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		break;
	case SDL_BUTTON_RIGHT:
		m_ProjectileManagerRef->TryAutoAttack(Point2f{ float(e.x),float(e.y) }, this,m_pAutoAttack);
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void Champion::OnMouseUp(const SDL_MouseButtonEvent& e)
{
	OnMouseUpBasic(e);
}

void Champion::OnMouseMotion(const SDL_MouseMotionEvent& e)
{
	OnMouseMotionBasic(e);
}

void Champion::OnKeyDown(const SDL_KeyboardEvent& e, const Point2f& mousePos)
{
	AbilityKey key{ GetAppropriateAbilityKey(e) };
	m_pAbilityInterface->OnPressAbility(key,OrientationManager::GetWorldLocation(mousePos));
}

void Champion::OnKeyHold(float elapsedSec, const Uint8* pStates, const Point2f& mousePos)
{
	{
		if (pStates[SDL_SCANCODE_Q])
		{
			m_pAbilityInterface->OnHoldingAbility(AbilityKey::Q, OrientationManager::GetWorldLocation(mousePos), elapsedSec);
		}
		if (pStates[SDL_SCANCODE_W])
		{
			m_pAbilityInterface->OnHoldingAbility(AbilityKey::W, OrientationManager::GetWorldLocation(mousePos), elapsedSec);
		}
		if (pStates[SDL_SCANCODE_E])
		{
			m_pAbilityInterface->OnHoldingAbility(AbilityKey::E, OrientationManager::GetWorldLocation(mousePos), elapsedSec);
		}
		if (pStates[SDL_SCANCODE_R])
		{
			m_pAbilityInterface->OnHoldingAbility(AbilityKey::R, OrientationManager::GetWorldLocation(mousePos), elapsedSec);
		}
		if (pStates[SDL_SCANCODE_D])
		{
			m_pAbilityInterface->OnHoldingAbility(AbilityKey::D, OrientationManager::GetWorldLocation(mousePos), elapsedSec);
		}
		if (pStates[SDL_SCANCODE_F])
		{
			m_pAbilityInterface->OnHoldingAbility(AbilityKey::F, OrientationManager::GetWorldLocation(mousePos), elapsedSec);
		}
	}
	//
	m_DrawAARange = pStates[SDL_SCANCODE_C];
}

void Champion::OnKeyUp(const SDL_KeyboardEvent& e, const Point2f& mousePos)
{
	AbilityKey key{ GetAppropriateAbilityKey(e) };
	m_pAbilityInterface->OnReleaseAbility(key, OrientationManager::GetWorldLocation(mousePos));
}

bool Champion::IsAutoAttackReady() const
{
	return m_pAutoAttackTimer->IsDone();
}

bool Champion::IsAAReadyAndReset()
{
	bool isDone{ m_pAutoAttackTimer->IsDone() };
	if (isDone)
	{
		m_pAutoAttackTimer->ResetTimer();
	}
	return isDone;
}

float Champion::GetAutoAttackRangeRadius() const
{
	return m_AutoAttackRangeRadius;
}

Unit* Champion::GetClosestUnit(std::vector<Unit*>* units) const
{
	float shortestDistance{ 1000.f };
	int index{ -1 };
	for (size_t i{ 0 }; i < units->size(); ++i)
	{
		float distance{ Vector2f{m_Transform.location - units->at(i)->GetTransform().location}.Length()};
		if (distance < shortestDistance)
		{
			index = int(i);
			shortestDistance = distance;
		}
	}
	if (index == -1)
	{
		return nullptr;
	}
	return units->at(index);
}

AbilityKey Champion::GetAppropriateAbilityKey(const SDL_KeyboardEvent& e) const
{
	AbilityKey key{ AbilityKey::undefined };
	switch (e.keysym.sym)
	{
	case SDLK_q:
		key = AbilityKey::Q;
		break;
	case SDLK_w:
		key = AbilityKey::W;
		break;
	case SDLK_e:
		key = AbilityKey::E;
		break;
	case SDLK_r:
		key = AbilityKey::R;
		break;
	case SDLK_d:
		key = AbilityKey::D;
		break;
	case SDLK_f:
		key = AbilityKey::F;
		break;
	}
	return key;
}

void Champion::DrawUnit() const
{
	using namespace utils;
	SetColor(Color4f{ 1,1,1,1 });
	FillEllipse(Point2f{ 0,0 }, 10, 10);

	FillRect(Point2f{ 0,-5 }, 15, 5);
}
