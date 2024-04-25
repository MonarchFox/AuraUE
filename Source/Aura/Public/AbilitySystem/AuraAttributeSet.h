// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


//? Forward Declarations
struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;

/**
 * @brief The FEffectProperty struct holds information about the source and target actors in an attribute change effect.
 *
 * The FEffectProperty struct is used to encapsulate information about the source and target actors in an attribute change effect.
 * It is typically used in conjunction with the AuraAttributeSet class to manage attribute changes.
 */
USTRUCT()
struct FEffectProperty
{
	GENERATED_BODY()
	FEffectProperty() {}
	FEffectProperty(UAbilitySystemComponent*  AbilitySystemComponent, AActor* AvtarActor,
		AController* Controller, ACharacter* Character): AbilitySystemComponent(AbilitySystemComponent),
	AvtarActor(AvtarActor), Controller(Controller), Character(Character) {}

	UPROPERTY()
	UAbilitySystemComponent*  AbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* AvtarActor = nullptr;
	UPROPERTY()
	AController* Controller = nullptr;
	UPROPERTY()
	ACharacter* Character = nullptr;
};


/**
 * @class UAuraAttributeSet
 * @brief This class represents the attribute set for the Aura system.
 *
 * The UAuraAttributeSet class is a subclass of UAttributeSet and contains
 * the attribute data for the Aura system. It includes attributes such as
 * HitPoints, MaxHitPoints, ManaPoints, and MaxManaPoints.
 */

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	//? Meta Information
	FGameplayEffectContextHandle EffectContextHandle;
	FEffectProperty SourceEffectProperty;
	FEffectProperty TargetEffectProperty;

	//? Meta Setters
	void PopulateEffectProperties(const FGameplayEffectModCallbackData& Data);
	FORCEINLINE void SetEffectContextHandle(const FGameplayEffectModCallbackData& Data) { EffectContextHandle = Data.EffectSpec.GetContext(); }

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	// Section Attributes

	// + HitPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_HitPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData HitPoints;
	UFUNCTION()
	void OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HitPoints);


	// + MaxHitPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_MaxHitPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData MaxHitPoints;
	UFUNCTION()
	void OnRep_MaxHitPoints(const FGameplayAttributeData& OldMaxHitPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHitPoints);

	
	// + ManaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_ManaPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData ManaPoints;
	UFUNCTION()
	void OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaPoints);

	
	// + MaxManaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_MaxManaPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData MaxManaPoints;
	UFUNCTION()
	void OnRep_MaxManaPoints(const FGameplayAttributeData& OldMaxManaPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxManaPoints);

	
	// + StaminaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_StaminaPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData StaminaPoints;
	UFUNCTION()
	void OnRep_StaminaPoints(const FGameplayAttributeData& OldStaminaPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaminaPoints);

	
	// + MaxStaminaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_MaxStaminaPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData MaxStaminaPoints;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxStaminaPoints);
	UFUNCTION()
	void OnRep_MaxStaminaPoints(const FGameplayAttributeData& OldMaxStaminaPoints) const;

	// End Attributes

protected:
	// Section Helper Methods

	//~ Helper Function For Storing Post Gameplay Effect Execute Data
	static void SetEffectProperty(UAbilitySystemComponent* AbilitySystemComponent, FEffectProperty& EffectProperty);

	//~ Helper Functions for Extracting information from `FGameplayEffectModCallbackData`
	static UAbilitySystemComponent* GetAbilitySystemComponent(const FGameplayEffectContextHandle& EffectContextHandle);
	
	static ACharacter* GetCharacter(const UAbilitySystemComponent* AbilitySystemComponent);
	static ACharacter* GetCharacter(const AController* Controller);
	
	static AController* GetController(const UAbilitySystemComponent* AbilitySystemComponent);
	static AController* GetController(const AActor* Actor);
	
	// End Helper Methods
};
