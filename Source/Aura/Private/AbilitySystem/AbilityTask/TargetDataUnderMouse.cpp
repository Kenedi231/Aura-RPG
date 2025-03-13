// Copyright myself


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

#include "Player/AuraPlayerController.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const AAuraPlayerController* AuraPC = Cast<AAuraPlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get());
	FHitResult CursorHit;
	AuraPC->GetCurrentCursorHit(CursorHit);

	ValidData.Broadcast(CursorHit.ImpactPoint);
}
