// Coded By MonarchFox


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

//~ Singleton Object Creation
FAuraGameplayTags FAuraGameplayTags::GameplayTags;

const FAuraGameplayTags& FAuraGameplayTags::Get()
{
	return GameplayTags;
}

void FAuraGameplayTags::InitNativeGameplayTags()
{
	//? Initializing Tags Aliases

	//~ Primary Attribute GameplayTags

	SetGameplayTag(GameplayTags.Attributes_Primary_Strength,
					FName("Attributes.Primary.Strength"));
	SetGameplayTag(GameplayTags.Attributes_Primary_Dexterity,
					FName("Attributes.Primary.Dexterity"));
	SetGameplayTag(GameplayTags.Attributes_Primary_Intelligence,
					FName("Attributes.Primary.Intelligence"));
	SetGameplayTag(GameplayTags.Attributes_Primary_Constitution,
					FName("Attributes.Primary.Constitution"));

	//~ Secondary Attribute GameplayTags
	
	// + Character Personal GameplayTags
	
	SetGameplayTag(GameplayTags.Attributes_Secondary_MaxHitPoints,
					FName("Attributes.Secondary.MaxHitPoints"));
	SetGameplayTag(GameplayTags.Attributes_Secondary_MaxMana,
					FName("Attributes.Secondary.MaxMana"));
	SetGameplayTag(GameplayTags.Attributes_Secondary_MaxStamina,
					FName("Attributes.Secondary.MaxStamina"));

	// + Armor GameplayTags

	SetGameplayTag(GameplayTags.Attributes_Secondary_Armor,
					FName("Attributes.Secondary.Armor"),
			FString("Physical Damage Reduction"));
	SetGameplayTag(GameplayTags.Attributes_Secondary_ArmorPenetration,
	FName("Attributes.Secondary.ArmorPenetration"),
	FString("Decreases HitTarget Armor Efficiency"));

	// + Critical GameplayTags
	
	SetGameplayTag(GameplayTags.Attributes_Secondary_CriticalChance,
					FName("Attributes.Secondary.CriticalChance"));
	SetGameplayTag(GameplayTags.Attributes_Secondary_CriticalDamage,
					FName("Attributes.Secondary.CriticalDamage"));
	SetGameplayTag(GameplayTags.Attributes_Secondary_CriticalResistance,
					FName("Attributes.Secondary.CriticalResistance"));

	// + Regeneration GameplayTags

	SetGameplayTag(GameplayTags.Attributes_Secondary_HealthRegeneration,
					FName("Attributes.Secondary.HealthRegeneration"));
	SetGameplayTag(GameplayTags.Attributes_Secondary_ManaRegeneration,
					FName("Attributes.Secondary.ManaRegeneration"));
}

void FAuraGameplayTags::SetGameplayTag(FGameplayTag& Tag, const FName TagName)
{
	Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(TagName);
}

void FAuraGameplayTags::SetGameplayTag(FGameplayTag& Tag, const FName TagName, const FString& DevComment)
{
	Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(TagName, DevComment);
}
