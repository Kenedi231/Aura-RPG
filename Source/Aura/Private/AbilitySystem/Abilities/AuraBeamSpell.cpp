// Copyright myself


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (!HitResult.bBlockingHit) {
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
		return;
	}

	MouseHitLocation = HitResult.ImpactPoint;
	MouseHitActor = HitResult.GetActor();
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if (OwnerCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);
			
			FHitResult HitResult;
			FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				SocketLocation,
				BeamTargetLocation,
				10.0f,
				TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,
				HitResult,
				true
			);

			if (HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}
	}

	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if (!CombatInterface->GetOnDeathSignature().IsAlreadyBound(this, &UAuraBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathSignature().AddDynamic(this, &UAuraBeamSpell::PrimaryTargetDied);
		}
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);
	
	TArray<AActor*> OverlappingActors;
	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
		GetAvatarActorFromActorInfo(),
		OverlappingActors,
		ActorsToIgnore,
		850.0f,
		MouseHitActor->GetActorLocation()
	);

	int32 NumAdditionalTargets = FMath::Min(MaxNumShockTargets, GetAbilityLevel() - 1);

	UAuraAbilitySystemLibrary::GetClosestTargets(NumAdditionalTargets, OverlappingActors, OutAdditionalTargets, MouseHitActor->GetActorLocation());

	for (AActor* Target : OutAdditionalTargets)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target))
		{
			if (!CombatInterface->GetOnDeathSignature().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied))
			{
				CombatInterface->GetOnDeathSignature().AddDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
			}
		}
	}
}
