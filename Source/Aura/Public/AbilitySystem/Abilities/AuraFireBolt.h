// Copyright myself

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch = false, float PitchOverride = 0.0f, AActor* HomingTarget = nullptr);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Fire Bolt")
	float ProjectileSpread = 90.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Fire Bolt")
	int32 MaxNumProjectiles = 5;
};
