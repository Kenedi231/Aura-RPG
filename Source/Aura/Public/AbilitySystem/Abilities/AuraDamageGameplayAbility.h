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

	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefault(AActor* TargetActor = nullptr, FVector InRadialDamageOrigin = FVector::ZeroVector, bool bOverrideKnockbackDirection = false, FVector InKnockbackDirectionOverride = FVector::ZeroVector, bool bOverrideDeathImpulse = false, FVector DeathImpulseDirectionOverride = FVector::ZeroVector, bool bOverridePitch = false, float PithOverride = 0.0f) const;

	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel() const;
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
	float DeathImpulseMagnitude = 1000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float KnockbackForceMagnitude = 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float KnockbackChange = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Radial Damage")
	bool bIsRadialDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Radial Damage")
	float RadialDamageInnerRadius = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Radial Damage")
	float RadialDamageOuterRadius = 0.0f;
	
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
};
