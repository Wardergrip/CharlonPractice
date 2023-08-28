#pragma once
struct BasicStats
{
	BasicStats(float maxHealth, float movementSpeed = 2, float maxMana = 100, float manaRegen = 1);
	BasicStats();
	float currentHealth;
	float maxHealth;
	// Returns (currentHealth / maxHealth)
	float GetPercentageHealth() const;

	float currentMana;
	float maxMana;
	// Returns (currentMana / maxMana)
	float GetPercentageMana() const;

	float movementSpeed;
	float manaRegen;

	void RegenMana(float elapsedSec);
};

