// Coded By MonarchFox

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"


AAuraEffectActor::AAuraEffectActor()
{
	// !Defaults
	PrimaryActorTick.bCanEverTick = false;
	GameplayEffectDurationType = EGameplayEffectDurationType::Instant;
}

/**
 * Begins play for the AuraEffectActor.
 *
 * This function is called when the AuraEffectActor is spawned and begins to play in the game world.
 *
 * It sets the Gameplay Effect Object Duration Type based on the default Gameplay Effect
 * associated with it. The Gameplay Effect Object Duration Type determines how long the
 * gameplay effect will last.
 */
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	//~ Setting Gameplay Effect Object Duration Type
	if (GetGameplayEffectObject())
	{
		if (const UGameplayEffect* GameplayEffect = GetGameplayEffectObject()->GetDefaultObject<UGameplayEffect>())
		{
			SetGameplayEffectDurationType(GameplayEffect->DurationPolicy);
		}
	}
}

/**
 * Applies the specified gameplay effect to the target actor.
 *
 * @param Target The actor to apply the gameplay effect to.
 * @param GameplayEffectClass The class of the gameplay effect to apply.
 */
void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target))
	{
		checkf(GameplayEffectClass, TEXT("GameEffectClass is null, Please Add Gameplay Effects"))

		// + Making Context
		FGameplayEffectContextHandle EffectContextHandle =  TargetAbilitySystemComponent->MakeEffectContext();

		// + Updating Context
		EffectContextHandle.AddSourceObject(this);

		// + No Idea
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->
		MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

		// + Applying Gameplay Effect
		 const FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
		 	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		//~ Storing TargetAbility System if Duration is Infinite
		if (GetGameplayEffectDurationType() == EGameplayEffectDurationType::Infinite &&
			GetEffectRemovalPolicy() == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandleMap.Add(TargetAbilitySystemComponent, ActiveGameplayEffectHandle);
		}
	}
}

/**
 * Applies the specified gameplay effect to the target actor when an overlap occurs.
 *
 * @param Target The actor that triggered the overlap.
 */
void AAuraEffectActor::GameplayEffectOnOverlap(AActor* Target)
{
	checkf(GetGameplayEffectObject(), TEXT("GameplayEffectObject is null, Please Add Gameplay Effects"))

	//~ Applying Polices
	if (GetEffectApplicationPolicy() == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(Target, GetGameplayEffectObject());
	}
}

/**
 * Executes the gameplay effect when the target actor ends overlap with the aura actor.
 *
 * @param Target The actor that ended overlap with the aura actor.
 */
void AAuraEffectActor::GameplayEffectOnEndOverlap(AActor* Target)
{
	checkf(GetGameplayEffectObject(), TEXT("GameplayEffectObject is null, Please Add Gameplay Effects"))

	//~ Applying Polices
	if (GetEffectApplicationPolicy() == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(Target, GetGameplayEffectObject());
	}

	//~ Removal Policies
	if (GetEffectRemovalPolicy() == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target))
		{
			if (ActiveEffectHandleMap.Find(AbilitySystemComponent))
			{
				AbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandleMap[AbilitySystemComponent], 1);
				ActiveEffectHandleMap.Remove(AbilitySystemComponent);
			}
		}
	}
}
