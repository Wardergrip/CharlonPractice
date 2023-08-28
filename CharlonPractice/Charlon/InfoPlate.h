#pragma once
#include "UserInterfaceElement.h"

#include "Vector2f.h"

class Texture;
class Unit;

class InfoPlate final : public UserInterfaceElement
{
// STATICS
public:
	static void SetDrawInfoPlates(bool state);
	static void SwitchDrawInfoPlates();
	static bool IsDrawingInfoPlates();

private:
	static bool c_EnableDrawInfoplates;

// NON STATICS
public:
	InfoPlate(const Unit* trackingUnit, const Vector2f& offset);
	InfoPlate(const Unit* trackingUnit);
	InfoPlate(const InfoPlate& infoplate) = delete;
	InfoPlate& operator=(const InfoPlate& infoplate) = delete;
	InfoPlate(InfoPlate&& infoplate) = delete;
	InfoPlate& operator=(InfoPlate&& infoplate) = delete;
	~InfoPlate();

	void Draw() const override;

	void SetName(const std::string& name);

private:
	const Unit* m_TrackingUnit;

	Vector2f m_Offset;
	Vector2f m_Scale;

	Rectf m_HealthBar;
	Color4f m_HealthBarColor;
	Rectf m_ManaBar;
	Color4f m_ManaBarColor;

	Texture* m_pName;
};

