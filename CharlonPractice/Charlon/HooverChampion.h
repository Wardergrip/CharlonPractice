#pragma once
#include "Champion.h"

class Texture;

class HooverChampion final : public Champion
{
public:
	HooverChampion(const Window& window, ProjectileManager* projectilemanagerref);
	HooverChampion(const HooverChampion& champ) = delete;
	HooverChampion& operator=(const HooverChampion& champ) = delete;
	HooverChampion(HooverChampion&& champ) = delete;
	HooverChampion& operator=(HooverChampion&& champ) = delete;
	virtual ~HooverChampion();

protected:
	virtual void DrawUnit() const override;

private:
	Texture* m_pBaseTxtrRef;
};

