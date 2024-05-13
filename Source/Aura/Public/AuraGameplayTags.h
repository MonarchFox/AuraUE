// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


//~ Forward Declarations

/**
 *		Singleton Object for Initializing Native Gameplay Tags
 */

struct FAuraGameplayTags
{
	//? Singleton Object
	static FAuraGameplayTags GameplayTags;

public:
	static const FAuraGameplayTags& Get();

	static void InitNativeGameplayTags();

	//~ Primary Attribute Tags
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Constitution;
	
	//~ Secondary Attribute Tags
	// +Character Personal
	FGameplayTag Attributes_Secondary_MaxHitPoints;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxStamina;
	
	// + Armor Stats
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;

	// + Critical Stats
	FGameplayTag Attributes_Secondary_CriticalChance;
	FGameplayTag Attributes_Secondary_CriticalDamage;
	FGameplayTag Attributes_Secondary_CriticalResistance;

	// + Regeneration Stats
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;

protected:
	static void SetGameplayTag(FGameplayTag& Tag, const FName TagName);
	static void SetGameplayTag(FGameplayTag& Tag, const FName TagName, const FString& DevComment);
};