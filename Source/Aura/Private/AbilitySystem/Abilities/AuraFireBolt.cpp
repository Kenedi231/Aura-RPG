// Copyright myself


#include "AbilitySystem/Abilities/AuraFireBolt.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			"<Title>FIRE BOLT</>\n"
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing: </>"
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),
			Level, -ManaCost, Cooldown, ScaledDamage);
	}

	return FString::Printf(TEXT(
		"<Title>FIRE BOLT</>\n"
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing: </>"
		"<Damage>%d</><Default> fire damage with"
		" a chance to burn</>"),
		Level, -ManaCost, Cooldown, FMath::Min(NumProjectiles, Level), ScaledDamage);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		"<Title>NEXT LEVEL: </>\n"
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
  		"<Default>Launches %d bolts of fire, "
		"exploding on impact and dealing: </>"
		"<Damage>%d</><Default> fire damage with"
		" a chance to burn</>"),
		Level, -ManaCost, Cooldown, FMath::Min(NumProjectiles, Level), ScaledDamage);
}