// Coded By MonarchFox


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bLocallyController = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bLocallyController)
	{
		SendMouseCursorData();
	}else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),
			GetActivationPredictionKey()).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);

		const bool bCalledDelegate = AbilitySystemComponent.Get()
									->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	//~ Scoped Prediction Window
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	const APlayerController* PlayerController =  Ability->GetCurrentActorInfo()->PlayerController.Get();

	//~ Creating Data for Delegating
	FHitResult CursorHit;
	FRotator Rotation;
	FVector StartLocation, EndLocation;
	PlayerController->GetPlayerViewPoint(StartLocation, Rotation);

	EndLocation = StartLocation + (Rotation.Vector() * 2000.f);
	FCollisionQueryParams TraceParams;
	GetWorld()->LineTraceSingleByChannel(CursorHit, StartLocation, EndLocation, ECC_Visibility, TraceParams);
	
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	FGameplayTag ApplicationTag;

	//~ Broadcasting Data
	AbilitySystemComponent->ServerSetReplicatedTargetData
	(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		ApplicationTag,
		AbilitySystemComponent->ScopedPredictionKey
	);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
