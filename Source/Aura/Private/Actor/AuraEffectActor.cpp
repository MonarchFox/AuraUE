// Coded By MonarchFox

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


AAuraEffectActor::AAuraEffectActor()
{
	// !Defaults
	PrimaryActorTick.bCanEverTick = true;
	
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

		FGameplayEffectContextHandle EffectContextHandle =  TargetAbilitySystemComponent->MakeEffectContext();

		EffectContextHandle.AddSourceObject(this);
		
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->
		MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);

		TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}
