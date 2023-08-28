#pragma once

#include "Ability.h"

class ExampleAbility final : public Ability
{
public:
	ExampleAbility(const std::string& key, const Point2f& championLocationRef);
	ExampleAbility(const ExampleAbility& ability) = delete;
	ExampleAbility& operator=(const ExampleAbility& ability) = delete;
	ExampleAbility(ExampleAbility&& ability) = delete;
	ExampleAbility& operator=(ExampleAbility&& ability) = delete;
	virtual ~ExampleAbility();

	void Draw() const override;

	bool OnPress(const Point2f& mousePos) override;
	bool OnHolding(float elapsedSec, const Point2f& mousePos) override;
	bool OnRelease(const Point2f& mousePos) override;

	virtual void Update(float elapsedSec) override;

private:
	const Point2f& m_ChampionLocationRef;
	Point2f m_LastMousePos;

	bool m_IsHoldingDown;
	float m_Range;

	void DrawIcon() const override;

};

