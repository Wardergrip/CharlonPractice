#include "pch.h"
#include "Ability.h"

#include "utils.h"

#include "Texture.h"
#include "Timer.h"
#include "CircleProgression.h"

#include <iostream>

using namespace utils;

// STATICS

ProjectileManager* Ability::c_ProjectileManagerRef{ nullptr };

void Ability::InitProjManager(ProjectileManager* projMan)
{
	c_ProjectileManagerRef = projMan;
}

// NON STATICS

Ability::Ability(Type type, const std::string& key, const std::string& name, float cooldown, int manaCost)
	:m_Type{type}
	,m_ShowTelegraph{false}
	,m_Cooldown{ new Timer{cooldown} }
	,m_Name{ name }
	,m_pButtonKeyTexture{ new Texture{key,"consola.ttf",20,Color4f{1,1,1,1}} }
	,m_pManaCostText{ new Texture{std::to_string(manaCost),"consola.ttf",20,Color4f{1,1,1,1}} }
	,m_Manacost{manaCost}
{
	m_pCircleProgression = new CircleProgression{ Point2f{25,25}, *m_Cooldown,true};
	m_pCircleProgression->FlipX();
	m_pCircleProgression->SetRad(23);
}

Ability::~Ability()
{
	delete m_pButtonKeyTexture;
	m_pButtonKeyTexture = nullptr;
	delete m_pManaCostText;
	m_pManaCostText = nullptr;
	delete m_Cooldown;
	m_Cooldown = nullptr;
	delete m_pCircleProgression;
	m_pCircleProgression = nullptr;
}

void Ability::DrawUI() const
{
	SetColor(Color4f{ 0.9f, 0.9f, 0.9f, 1 });
	DrawRect(Rectf{ 0,0,50,50 });
	if (this)
	{
		if (!m_Cooldown->IsDone())
		{
			SetColor(Color4f{ 1,0.8f,0,0.5f });
			m_pCircleProgression->Draw();
		}
	}
	if (this == nullptr) return;
	m_pButtonKeyTexture->Draw(Point2f{2,1});
	m_pManaCostText->Draw(Point2f{ 50-m_pManaCostText->GetWidth() - 3, 1});
	DrawIcon();
}

int Ability::GetManaCost() const
{
	return m_Manacost;
}
