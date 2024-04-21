// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

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

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Section Attribute Components

	// + HitPoints Attribute
	UPROPERTY(ReplicatedUsing=OnRep_HitPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData HitPoints;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HitPoints);
	
	UFUNCTION()
	void OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints) const;

	// + MaxHitPoints Attribute

	UPROPERTY(ReplicatedUsing=OnRep_MaxHitPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData MaxHitPoints;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHitPoints);

	UFUNCTION()
	void OnRep_MaxHitPoints(const FGameplayAttributeData& OldMaxHitPoints) const;

	// + ManaPoints Attribute
	UPROPERTY(ReplicatedUsing=OnRep_ManaPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData ManaPoints;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaPoints);
	
	UFUNCTION()
	void OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints) const;

	// + MaxManaPoints Attribute
	
	UPROPERTY(ReplicatedUsing=OnRep_MaxManaPoints, BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData MaxManaPoints;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxManaPoints);

	UFUNCTION()
	void OnRep_MaxManaPoints(const FGameplayAttributeData& OldMaxManaPoints) const;
	
	// End Section
};
