#pragma once
#include <string>

class Texture;
class Timer;

class ProjectileManager;
class CircleProgression;

class Ability
{
public:
	static void InitProjManager(ProjectileManager* projMan);
protected:
	static ProjectileManager* c_ProjectileManagerRef;
public:
	enum class Type
	{
		selfCast, enemyCast, skillshot
	};

	Ability(Type type, const std::string& key, const std::string& name = "Default name", float cooldown = 0, int manaCost = 0);
	Ability(const Ability& ability) = delete;
	Ability& operator=(const Ability& ability) = delete;
	Ability(Ability&& ability) = delete;
	Ability& operator=(Ability&& ability) = delete;
	virtual ~Ability();

	virtual void Draw() const = 0;
	void DrawUI() const;

	// Returns true if mana should be deducted from the using champion.
	virtual bool OnPress(const Point2f& mousePos) = 0;
	// Returns true if mana should be deducted from the using champion.
	virtual bool OnHolding(float elapsedSec, const Point2f& mousePos) = 0;
	// Returns true if mana should be deducted from the using champion.
	virtual bool OnRelease(const Point2f& mousePos) = 0;

	// Returns true if mana should be deducted from the using champion.
	virtual void Update(float elapsedSec) = 0;

	virtual int GetManaCost() const;
protected:
	const Type m_Type;

	int m_Manacost;
	bool m_ShowTelegraph;

	std::string m_Name;
	Timer* m_Cooldown;
	CircleProgression* m_pCircleProgression;

	Texture* m_pButtonKeyTexture;
	Texture* m_pManaCostText;

	virtual void DrawIcon() const = 0;
};

