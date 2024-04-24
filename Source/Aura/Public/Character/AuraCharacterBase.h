// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "AuraCharacterBase.generated.h"


/*
 *		!Base Character Class
 */


class UAttributeSet;
class UAbilitySystemComponent;


UCLASS(Abstract, NotBlueprintable)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	//? meta information
    bool ReplicationRequired { true };

public:
	AAuraCharacterBase();

	//~ Getters and Setters For Gameplay Ability System
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return PAbilitySystemComponent; }
	FORCEINLINE void SetAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent) { PAbilitySystemComponent = AbilitySystemComponent; }

	FORCEINLINE UAttributeSet* GetAttributeSet () const { return PAttributeSet; }
	FORCEINLINE void SetAttributeSet(UAttributeSet* AttributeSet) { PAttributeSet = AttributeSet; }


protected:
	virtual void BeginPlay() override;

	//~ Gameplay Ability System Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> PAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> PAttributeSet;

	
	// Section Cosmetics References
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponComponentSocketName { "WeaponHandSocket" };

	// End

public:
		
	/** ? Getters */
	FORCEINLINE bool IsReplicationRequired() const { return ReplicationRequired; }
};
