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

	//~ Getters For Gameplay Ability System
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet () const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	//~ Gameplay Ability System Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;

	
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
