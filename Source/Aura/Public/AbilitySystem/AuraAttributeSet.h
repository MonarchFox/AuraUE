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

/**s
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
	
	/**
	 *
	 *			Section Primary Attributes
	 * 
	 */


	/** + Strength: Represents physical damage */
	UPROPERTY(ReplicatedUsing=OnRep_Strength, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& STR) const;

	/** + Constitution: Represent Health Capacity and Body Defense */
	UPROPERTY(ReplicatedUsing=OnRep_Constitution, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Constitution;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Constitution);
	UFUNCTION()
	void OnRep_Constitution(const FGameplayAttributeData& CON) const;

	/** + Dexterity: Represent Health Capacity and Body Defense */
	UPROPERTY(ReplicatedUsing=OnRep_Dexterity, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Dexterity);
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& CON) const;

	/** + Intelligence Represent Magical damage and Mana Capacity */
	UPROPERTY(ReplicatedUsing=OnRep_Intelligence, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& INT) const;

	/** + FOCUS Increases Healing and Buff strength */
	UPROPERTY(ReplicatedUsing=OnRep_Focus, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Focus;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Focus);
	UFUNCTION()
	void OnRep_Focus(const FGameplayAttributeData& FOC) const;

	/** + LUCK Makes you Lucky */
	UPROPERTY(ReplicatedUsing=OnRep_Luck, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Luck;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Luck);
	UFUNCTION()
	void OnRep_Luck(const FGameplayAttributeData& LUC) const;


	//			End Primary Attributes

	/**
	 *
	 *			Section Secondary Attributes
	 * 
	 */

	/** + Armor  Makes*/
	UPROPERTY(ReplicatedUsing=OnRep_Armor, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& NewValue) const;
	//? [(Cons * 0.15) + (Str * 0.02)] + 5 
	
	/** + ArmorPenetration */
	UPROPERTY(ReplicatedUsing=OnRep_ArmorPenetration, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& NewValue) const;
	//? [(Dex * .05) + (STR * 0.15)] + 5
	
	/** + CriticalChance */
	UPROPERTY(ReplicatedUsing=OnRep_CriticalChance, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalChance);
	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& NewValue) const;
	//? (Dex * 0.15) + (WillType * 0.15) - (ArmorPenetration - Cons * 0.15)
	
	/** + CriticalDamage */
	UPROPERTY(ReplicatedUsing=OnRep_CriticalDamage, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalDamage);
	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& NewValue) const;
	//? [(Dex * 0.30) + (Str * .20)]
	
	/** + CriticalResistance */
	UPROPERTY(ReplicatedUsing=OnRep_CriticalResistance, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData CriticalResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalResistance);
	UFUNCTION()
	void OnRep_CriticalResistance(const FGameplayAttributeData& NewValue) const;
	//? Cons * 0.15 + str * 0.05
	
	/** + HealthRegeneration */
	UPROPERTY(ReplicatedUsing=OnRep_Focus, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& NewValue) const;
	//? Cons * 0.05 + 1
	
	/** + ManaRegeneration */
	UPROPERTY(ReplicatedUsing=OnRep_ManaRegeneration, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& NewValue) const;
	//? INT * 0.05 + 1
	
	/** + Stun duration on receive */
	UPROPERTY(ReplicatedUsing=OnRep_Stun, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Stun;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Stun);
	UFUNCTION()
	void OnRep_Stun(const FGameplayAttributeData& NewValue) const;
	//? 1 / (1 - [(Refresh / 100) + willpower * 0.15)]
	
	/** + Refresh refreshes from
	 * + Crowd effect attacks 
	 *	+ ArmourBreak
	 *	+ WillPower Break
	 */
	UPROPERTY(ReplicatedUsing=OnRep_Refresh, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData Refresh;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Refresh);
	UFUNCTION()
	void OnRep_Refresh(const FGameplayAttributeData& NewValue) const;
	//? WillPower * 0.5
	
	/** + on ArmorBreak (takes more damage for some time) */
	UPROPERTY(ReplicatedUsing=OnRep_ArmorBreak, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData ArmorBreak;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorBreak);
	UFUNCTION()
	void OnRep_ArmorBreak(const FGameplayAttributeData& NewValue) const;
	//?  1 / (1 - [(Refresh / 100) + willpower * 0.25 + Cons * 10)]
	
	//? Secondary Types will be used for items
	/** + FireType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_FireType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData FireType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireType);
	UFUNCTION()
	void OnRep_FireType(const FGameplayAttributeData& NewValue) const;
	
	/** + IceType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_IceType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData IceType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IceType);
	UFUNCTION()
	void OnRep_IceType(const FGameplayAttributeData& NewValue) const;
	
	/** + WaterType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_WaterType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData WaterType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, WaterType);
	UFUNCTION()
	void OnRep_WaterType(const FGameplayAttributeData& NewValue) const;
	
	/** + ElectricType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_ElectricType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData ElectricType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ElectricType);
	UFUNCTION()
	void OnRep_ElectricType(const FGameplayAttributeData& NewValue) const;
	
	/** + WindType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_WindType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData WindType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, WindType);
	UFUNCTION()
	void OnRep_WindType(const FGameplayAttributeData& NewValue) const;
	
	/** + GrassType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_GrassType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData GrassType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, GrassType);
	UFUNCTION()
	void OnRep_GrassType(const FGameplayAttributeData& NewValue) const;
	
	/** + ArcaneType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_ArcaneType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData ArcaneType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArcaneType);
	UFUNCTION()
	void OnRep_ArcaneType(const FGameplayAttributeData& NewValue) const;
	
	/** + VoidType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_VoidType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData VoidType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, VoidType);
	UFUNCTION()
	void OnRep_VoidType(const FGameplayAttributeData& NewValue) const;
	
	/** + WILLType Resistance and Attack */
	UPROPERTY(ReplicatedUsing=OnRep_WILLType, BlueprintReadOnly, Category="Attribute|Primary")
	FGameplayAttributeData WILLType;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, WILLType);
	UFUNCTION()
	void OnRep_WILLType(const FGameplayAttributeData& NewValue) const;

	
	// End Secondary Attributes

	
	/**
	 *
	 *			Section Vital Attributes
	 * 
	 */

	// + HitPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_HitPoints, BlueprintReadOnly, Category="Attribute|vital")
	FGameplayAttributeData HitPoints;
	UFUNCTION()
	void OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HitPoints);

	// + MaxHitPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_MaxHitPoints, BlueprintReadOnly, Category="Attribute|vital")
	FGameplayAttributeData MaxHitPoints;
	UFUNCTION()
	void OnRep_MaxHitPoints(const FGameplayAttributeData& OldMaxHitPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHitPoints);
	
	// + ManaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_ManaPoints, BlueprintReadOnly, Category="Attribute|vital")
	FGameplayAttributeData ManaPoints;
	UFUNCTION()
	void OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaPoints);
	
	// + MaxManaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_MaxManaPoints, BlueprintReadOnly, Category="Attribute|vital")
	FGameplayAttributeData MaxManaPoints;
	UFUNCTION()
	void OnRep_MaxManaPoints(const FGameplayAttributeData& OldMaxManaPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxManaPoints);
	
	// + StaminaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_StaminaPoints, BlueprintReadOnly, Category="Attribute|vital")
	FGameplayAttributeData StaminaPoints;
	UFUNCTION()
	void OnRep_StaminaPoints(const FGameplayAttributeData& OldStaminaPoints) const;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaminaPoints);
	
	// + MaxStaminaPoints Property
	UPROPERTY(ReplicatedUsing=OnRep_MaxStaminaPoints, BlueprintReadOnly, Category="Attribute|vital")
	FGameplayAttributeData MaxStaminaPoints;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxStaminaPoints);
	UFUNCTION()
	void OnRep_MaxStaminaPoints(const FGameplayAttributeData& OldMaxStaminaPoints) const;

	//			End Vital Attributes

protected:
	//			Section Helper Methods

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
