// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

/**
 * @class AAuraPlayerState
 *
 * @brief The AAuraPlayerState class is a player state class used in the Aura game.
 *
 * This class inherits from the APlayerState class provided by the engine. It includes
 * additional functionality specific to the Aura game.
 */


class UAttributeSet;
class UAbilitySystemComponent;


UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	// ? meta information
	float ClientUpdateFrequency { 100.f };
	bool ReplicationRequired { true };
	
public:
	AAuraPlayerState();
	
	//~ AbilitySystemInterface Getters
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	// ? Other Getters
	FORCEINLINE float GetClientUpdateFrequency() const { return ClientUpdateFrequency; }
	FORCEINLINE bool IsReplicationRequired() const { return ReplicationRequired; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
protected:

	// Section Ability System State

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

	// End Ability System State
};
