// Copyright myself

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	FDamageEffectParams MakeDamageEffectParamsFromClassDefault(AActor* TargetActor = nullptr) const;
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	float DebuffChance = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	float DebuffDamage = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	float DebuffFrequency = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	float DebuffDuration = 5.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Debuff")
	float DeathImpulseMagnitude = 60.0f;
	

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
};
