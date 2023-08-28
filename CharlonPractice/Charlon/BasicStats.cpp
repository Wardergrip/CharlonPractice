#include "pch.h"
#include "BasicStats.h"

BasicStats::BasicStats(float maxHealth, float movementSpeed, float maxMana, float manaRegen)
    :movementSpeed{movementSpeed}
    ,maxHealth{maxHealth}
    ,currentHealth{maxHealth}
    ,maxMana{maxMana}
    ,currentMana{maxMana}
    ,manaRegen{manaRegen}
{
}

BasicStats::BasicStats()
    :BasicStats(100,2,100)
{
}

float BasicStats::GetPercentageHealth() const
{
    return (currentHealth / maxHealth);
}

float BasicStats::GetPercentageMana() const
{
    return (currentMana / maxMana);
}

void BasicStats::RegenMana(float elapsedSec)
{
    if (currentMana < maxMana)
    {
        currentMana += manaRegen * elapsedSec;
        if (currentMana > maxMana)
        {
            currentMana = maxMana;
        }
    }
}
