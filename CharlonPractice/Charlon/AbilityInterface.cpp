#include "pch.h"
#include "AbilityInterface.h"

#include <iostream>

#include "Ability.h"

#include "utils.h"
using namespace utils;

#include "Champion.h"

std::ostream& operator<<(std::ostream& out, AbilityKey key)
{
	out << "[";
	switch (key)
	{
	case AbilityKey::Q:
		out << "Q";
		break;
	case AbilityKey::W:
		out << "W";
		break;
	case AbilityKey::E:
		out << "E";
		break;
	case AbilityKey::R:
		out << "R";
		break;
	case AbilityKey::D:
		out << "D";
		break;
	case AbilityKey::F:
		out << "F";
		break;
	case AbilityKey::undefined:
		out << "undefined";
		break;
	default:
		out << "not implemented";
		break;
	}
	out << "]";
	return out;
}

char KeyToChar(AbilityKey key)
{
	char output{ '.' };
	switch (key)
	{
	case AbilityKey::Q:
		output = 'Q';
		break;
	case AbilityKey::W:
		output = 'W';
		break;
	case AbilityKey::E:
		output = 'E';
		break;
	case AbilityKey::R:
		output = 'R';
		break;
	case AbilityKey::D:
		output = 'D';
		break;
	case AbilityKey::F:
		output = 'F';
		break;
	case AbilityKey::undefined:
		output = '%';
		break;
	default:
		break;
	}
	return output;
}

// //////////////////////////////////////////////////////////////////////////////

AbilityInterface::AbilityInterface(const Window& window, Champion* owner, const Vector2f& scale)
	:UserInterfaceElement(m_Base)
	,m_pAbilities{}
	,m_Base{}
	,m_Scale{scale}
	,m_Middle{}
	,m_pOwnerRef{owner}
{
	if (m_Scale.x == 0 && m_Scale.y == 0)
	{
		m_Scale = Vector2f{ 1,1 };
	}
	float width{ 340 }, height{10};
	m_Base = Rectf{ window.width / 2 - width / 2, height, width, 60 };
	m_Middle = Point2f{ window.width / 2, height };
	for (int i{ 0 }; i < int(AbilityKey::undefined); ++i)
	{
		m_pAbilities.push_back(nullptr);
	}

	if (owner == nullptr)
	{
		std::cout << "Owner can't be nullptr! Deleting self\n";
		delete this;
		return;
	}
}

AbilityInterface::~AbilityInterface()
{
	for (size_t idx{ 0 }; idx < m_pAbilities.size(); ++idx)
	{
		delete m_pAbilities[idx];
		m_pAbilities[idx] = nullptr;
	}
}

void AbilityInterface::Draw() const
{
	// Base
	SetColor(Color4f{ 1,1,1,0.5f });
	glPushMatrix();
	{
		glTranslatef(m_Middle.x, m_Middle.y, 0);
		glScalef(m_Scale.x, m_Scale.y, 1);
		glTranslatef(-m_Base.width / 2, 0, 0);
		FillRect(Rectf{0,0,m_Base.width,m_Base.height});
		glTranslatef(5,5,0);
		for (size_t idx{0}; idx < m_pAbilities.size(); ++idx)
		{
			m_pAbilities[idx]->DrawUI();
			glTranslatef(55, 0, 0);
		}
	}
	glPopMatrix();
}

void AbilityInterface::DrawAbilities() const
{
	for (auto ability : m_pAbilities)
	{
		if (ability == nullptr) continue;
		ability->Draw();
	}
}

void AbilityInterface::Update(float elapsedSec)
{
	for (size_t i{ 0 }; i < m_pAbilities.size(); ++i)
	{
		if (m_pAbilities[i] == nullptr)
		{
			continue;
		}
		m_pAbilities[i]->Update(elapsedSec);
	}
}

void AbilityInterface::AssignAbility(AbilityKey idx, Ability* ability)
{
	delete m_pAbilities[int(idx)];
	m_pAbilities[int(idx)] = ability;
}

void AbilityInterface::OnPressAbility(AbilityKey key, const Point2f& mousePos)
{
	if (key == AbilityKey::undefined) return;
	if (m_pOwnerRef->GetBasicStats().currentMana >= m_pAbilities[size_t(key)]->GetManaCost())
	{
		if (m_pAbilities[size_t(key)]->OnPress(mousePos))
		{
			m_pOwnerRef->TakeMana(m_pAbilities[size_t(key)]->GetManaCost());
		}
	}
}

void AbilityInterface::OnHoldingAbility(AbilityKey key, const Point2f& mousePos, float elapsedSec)
{
	if (key == AbilityKey::undefined) return;
	if (m_pOwnerRef->GetBasicStats().currentMana >= m_pAbilities[size_t(key)]->GetManaCost())
	{
		if (m_pAbilities[size_t(key)]->OnHolding(elapsedSec, mousePos))
		{
			m_pOwnerRef->TakeMana(m_pAbilities[size_t(key)]->GetManaCost());
		}
	}
}

void AbilityInterface::OnReleaseAbility(AbilityKey key, const Point2f& mousePos)
{
	if (key == AbilityKey::undefined) return;
	if (m_pOwnerRef->GetBasicStats().currentMana >= m_pAbilities[size_t(key)]->GetManaCost())
	{
		if (m_pAbilities[size_t(key)]->OnRelease(mousePos))
		{
			m_pOwnerRef->TakeMana(m_pAbilities[size_t(key)]->GetManaCost());
		}
	}
}

void AbilityInterface::ChangeScale(const Vector2f& scaleVector)
{
	m_Scale = scaleVector;
}

void AbilityInterface::ChangeScale(float scale)
{
	m_Scale.x = scale;
	m_Scale.y = scale;
}

Vector2f AbilityInterface::GetScale() const
{
	return m_Scale;
}

