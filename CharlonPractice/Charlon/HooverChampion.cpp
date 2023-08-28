#include "pch.h"
#include "HooverChampion.h"

#include "ResourceManager.h"
#include "Texture.h"
#include "ExampleAbility.h"
#include "AutoAttack.h"

HooverChampion::HooverChampion(const Window& window, ProjectileManager* projectilemanagerref)
	:Champion(window,projectilemanagerref,"Hoover",false)
{
	using Textures = ResourceManager::Textures;
	m_pBaseTxtrRef = ResourceManager::GetTexture(Textures::hoover);

	// Abilities
	m_pAbilityInterface->AssignAbility(AbilityKey::Q, new ExampleAbility("Q", this->m_Transform.location));
	// AutoAttack
	m_pAutoAttack = new AutoAttack(m_Transform.location, nullptr);
}

HooverChampion::~HooverChampion()
{
	// DO NOT DELETE REFS
}

void HooverChampion::DrawUnit() const
{
	m_pBaseTxtrRef->Draw(Point2f{-m_pBaseTxtrRef->GetWidth() / 2, -m_pBaseTxtrRef->GetHeight() / 2});
}
