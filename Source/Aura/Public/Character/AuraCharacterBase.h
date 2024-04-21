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

	// Section Interfaces

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	
	// Section End
	
	//? Getters
	FORCEINLINE bool IsReplicationRequired() const { return ReplicationRequired; }
	FORCEINLINE UAttributeSet* GetAttributeSet () const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	// Section StaticMeshComponent References
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponComponentSocketName { "WeaponHandSocket" };

	// End

	// Section Ability System Components

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
	
	// End
};
