// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/** Asset Tag */
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer);


/**
 * @class UAuraAbilitySystemComponent
 *
 * @brief Represents the ability system component for the Aura game.
 *
 * The UAuraAbilitySystemComponent is a subclass of UAbilitySystemComponent and is used to manage abilities and
 * gameplay effects for the Aura game. It provides functionality for activating and deactivating abilities and
 * applying gameplay effects to actors.
 *
 * This class provides a central place to manage abilities and effects for all actors in the game that have an
 * AbilitySystemComponent. Each actor that needs abilities and effects should include this component as part of
 * its class hierarchy.
 *
 * @see UAbilitySystemComponent
 */

UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;

	//~ Grants Ability
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	//~ Ability Calls
	void AbilityInputTagHeld(const FGameplayTag& GameplayTag);
	void AbilityInputTagReleased(const FGameplayTag& GameplayTag);
	
	//~ Delegate Bindings
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
