// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "AuraCharacterBase.generated.h"



class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;


/**
 *	Character Base Class
 */
UCLASS(Abstract, NotBlueprintable)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	//? meta information

	/** + Replication meta information */
    bool ReplicationRequired { true };

	/** +Attributes meta information */
	UPROPERTY(EditAnywhere, Category="Attribute|Primary", BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttribute;

public:
	AAuraCharacterBase();

	//~ Getters and Setters For Gameplay Ability System
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return PAbilitySystemComponent; }
	FORCEINLINE void SetAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent) { PAbilitySystemComponent = AbilitySystemComponent; }

	FORCEINLINE UAttributeSet* GetAttributeSet () const { return PAttributeSet; }
	FORCEINLINE void SetAttributeSet(UAttributeSet* AttributeSet) { PAttributeSet = AttributeSet; }

	FORCEINLINE TSubclassOf<UGameplayEffect> GetDefaultPrimaryAttribute() const { return DefaultPrimaryAttribute; }


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

	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponComponentSocketName { "WeaponHandSocket" };

	// End

	//~ Initial Attribute Setter
	void InitialPrimaryAttribute() const;

public:
		
	/** ? Getters */
	FORCEINLINE bool IsReplicationRequired() const { return ReplicationRequired; }
};
