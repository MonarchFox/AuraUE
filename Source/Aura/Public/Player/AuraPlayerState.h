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

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"), ReplicatedUsing=OnRep_Level)
	int32 PlayerLevel {1};
	
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//~ Replicable Functions
	UFUNCTION()
	void OnRep_Level(int32 OldLevel) const;
	
protected:

	//~ Gameplay Ability System Components  
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

public:
	/** ? Getters amd Setters */

	//~ Gameplay Ability System Getters
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	//~ Replication Getters
	FORCEINLINE float GetClientUpdateFrequency() const { return ClientUpdateFrequency; }
	FORCEINLINE bool IsReplicationRequired() const { return ReplicationRequired; }
	FORCEINLINE int32 GetPlayerLevel() const { return PlayerLevel; }
};
