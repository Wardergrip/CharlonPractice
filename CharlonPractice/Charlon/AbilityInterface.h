#pragma once
#include <vector>
#include <iostream>

#include "structs.h"
#include "Vector2f.h"
#include "UserInterfaceElement.h"

enum class AbilityKey { Q, W, E, R, D, F, undefined };

std::ostream& operator<< (std::ostream& out, AbilityKey key);
char KeyToChar(AbilityKey key);

class Ability;
class Champion;

class AbilityInterface final : public UserInterfaceElement
{
public:

	AbilityInterface(const Window& window, Champion* owner, const Vector2f& scale = {});
	AbilityInterface(const AbilityInterface& abilityinterface) = delete;
	AbilityInterface& operator=(const AbilityInterface& abilityinterface) = delete;
	AbilityInterface(AbilityInterface&& abilityinterface) = delete;
	AbilityInterface& operator=(AbilityInterface&& abilityinterface) = delete;
	~AbilityInterface();

	void Draw() const override;
	void DrawAbilities() const;
	void Update(float elapsedSec);

	// Overrides ability in case a ability is already assigned
	void AssignAbility(AbilityKey idx, Ability* ability);

	void OnPressAbility(AbilityKey key, const Point2f& mousePos);
	void OnHoldingAbility(AbilityKey key, const Point2f& mousePos, float elapsedSec);
	void OnReleaseAbility(AbilityKey key, const Point2f& mousePos);

	void ChangeScale(const Vector2f& scaleVector);
	void ChangeScale(float scale);
	Vector2f GetScale() const;

private:
	std::vector<Ability*> m_pAbilities;
	Rectf m_Base;
	Point2f m_Middle;
	Vector2f m_Scale;
	Champion* m_pOwnerRef;
};

