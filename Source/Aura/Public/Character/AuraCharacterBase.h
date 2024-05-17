// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"

#include "AuraCharacterBase.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;


/**
 *	Character Base Class
 */
UCLASS(Abstract, NotBlueprintable)
class AURA_API AAuraCharacterBase :	public ACharacter,
									public IAbilitySystemInterface,
									public ICombatInterface
{
	GENERATED_BODY()
	
	//? meta information
	/** + Abilities */
	UPROPERTY(EditAnywhere, Category="Custom|Ability", meta=(AllowPrivateAccess))
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	/** + Replication meta information */
    bool ReplicationRequired { true };

	/** + Attributes meta information */
	UPROPERTY(EditAnywhere, Category="Attribute|Primary", BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttribute;

	UPROPERTY(EditAnywhere, Category="Attribute|Secondary", BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttribute;

public:
	AAuraCharacterBase();

	//~ Interfaces

	//+ CombatInterface
	virtual FVector GetCombatSocketLocation() const override;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();

	//~ Gameplay Ability System Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> PAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> PAttributeSet;
	
	// Section Cosmetics References
	
	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponComponentSocketName { "WeaponHandSocket" };

	// End

	//~ Initial Attribute Setter
	void InitGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> AttributeEffect, const float Level) const;
	void InitialDefaultAttributes() const;
	
public:

	/** ? Abilities */
	void AddCharacterAbility();
	
	/** ? Getters */
	
	//~ Getters and Setters For Gameplay Ability System
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return PAbilitySystemComponent; }
	FORCEINLINE void SetAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent) { PAbilitySystemComponent = AbilitySystemComponent; }

	FORCEINLINE UAttributeSet* GetAttributeSet () const { return PAttributeSet; }
	FORCEINLINE void SetAttributeSet(UAttributeSet* AttributeSet) { PAttributeSet = AttributeSet; }

	FORCEINLINE TSubclassOf<UGameplayEffect> GetDefaultPrimaryAttribute() const { return DefaultPrimaryAttribute; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetDefaultSecondaryAttribute() const { return DefaultSecondaryAttribute; }

	//~ Replications
	FORCEINLINE bool IsReplicationRequired() const { return ReplicationRequired; }
};
