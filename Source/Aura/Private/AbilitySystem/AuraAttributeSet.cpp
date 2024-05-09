// Coded By MonarchFox

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	// !Defaults
	
	//? For Debug Purpose Only
	InitHitPoints(100.f);
	InitManaPoints(100.f);
}

/**
 *
 *			Section Primary Attributes Replication
 * 
 */

/**
 * GetLifetimeReplicatedProps function for setting up the replicated properties of the UAuraAttributeSet class.
 *
 * @param OutLifetimeProps A reference to an array of FLifetimeProperty objects that will store the replicated properties.
 *                         Any replicated properties added to this array will be automatically replicated to the clients.
 *                         This parameter is modified and should be passed by reference.
 * @return void
 *
 * @see UAuraAttributeSet
 */
// TODO: Add Left Over Attributes
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// !Replication Properties Setup
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// + Vita; Attribute Setup
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HitPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHitPoints, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxManaPoints, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, StaminaPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxStaminaPoints, COND_None, REPNOTIFY_Always);

	// + Primary Attribute Setup
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Constitution, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Focus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Luck, COND_None, REPNOTIFY_Always);

	// + Secondary Attribute Setup
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Stun, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Refresh, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorBreak, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, FireType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, IceType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, WaterType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ElectricType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, WindType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, GrassType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArcaneType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, VoidType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, WILLType, COND_None, REPNOTIFY_Always);
}

/** + Strength: Represents physical damage */
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& STR) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, STR);
}

/** + Constitution: Represent Health Capacity and Body Defense */
void UAuraAttributeSet::OnRep_Constitution(const FGameplayAttributeData& CON) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Constitution, CON);
}

/** + Dexterity: Represent Health Capacity and Body Defense */
void UAuraAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& DEX) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Dexterity, DEX);
}

/** + Intelligence Represent Magical damage and Mana Capacity */
void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& INT) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, INT);
}

/** + FOCUS Increases Healing and Buff strength */
void UAuraAttributeSet::OnRep_Focus(const FGameplayAttributeData& FOC) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Focus, FOC);
}

/** + LUCK Makes you Lucky */
void UAuraAttributeSet::OnRep_Luck(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Luck, NewValue);
}

/** Section Secondary Attributes **/

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, NewValue);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, NewValue);
}

void UAuraAttributeSet::OnRep_CriticalChance(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalChance, NewValue);
}

void UAuraAttributeSet::OnRep_CriticalDamage(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalDamage, NewValue);
}

void UAuraAttributeSet::OnRep_CriticalResistance(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalResistance, NewValue);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, NewValue);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, NewValue);
}

void UAuraAttributeSet::OnRep_Stun(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Stun, NewValue);
}

void UAuraAttributeSet::OnRep_Refresh(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Refresh, NewValue);
}

void UAuraAttributeSet::OnRep_ArmorBreak(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorBreak, NewValue);
}

void UAuraAttributeSet::OnRep_FireType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireType, NewValue);
}

void UAuraAttributeSet::OnRep_IceType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, IceType, NewValue);
}

void UAuraAttributeSet::OnRep_WaterType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, WaterType, NewValue);
}

void UAuraAttributeSet::OnRep_ElectricType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ElectricType, NewValue);
}

void UAuraAttributeSet::OnRep_WindType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, WindType, NewValue);
}

void UAuraAttributeSet::OnRep_GrassType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, GrassType, NewValue);
}

void UAuraAttributeSet::OnRep_ArcaneType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArcaneType, NewValue);
}

void UAuraAttributeSet::OnRep_VoidType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, VoidType, NewValue);
}


/** Section Vital Attributes **/

void UAuraAttributeSet::OnRep_WILLType(const FGameplayAttributeData& NewValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, WILLType, NewValue);
}

// + HitPoints Attribute Replication
/**
 * Notify function for when the "Hitpoints" attribute is replicated from the server to the clients.
 *
 * @param OldHitPoints The previous value of the "HitPoints" attribute.
 */
void UAuraAttributeSet::OnRep_HitPoints(const FGameplayAttributeData& OldHitPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HitPoints, OldHitPoints);
}

// + MaxHitPoints Attribute Replication
/**
 * Notify function for when the "MaxHitPoints" attribute is replicated from the server to the clients.
 *
 * @param OldMaxHitPoints The previous value of the "MaxHitPoints" attribute.
 */
void UAuraAttributeSet::OnRep_MaxHitPoints(const FGameplayAttributeData& OldMaxHitPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHitPoints, OldMaxHitPoints);
}

// + ManaPoints Attribute Replications

/**
 * Notify function for when the "ManaPoints" attribute is replicated from the server to the clients.
 *
 * @param OldManaPoints The previous value of the "ManaPoints" attribute.
 */
void UAuraAttributeSet::OnRep_ManaPoints(const FGameplayAttributeData& OldManaPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaPoints, OldManaPoints);
}

// + MaxManaPoints Attribute Replication
/**
 * Notify function for when the "MaxManaPoints" attribute is replicated from the server to the clients.
 *
 * @param OldMaxManaPoints The previous value of the "MaxManaPoints" attribute.
 */
void UAuraAttributeSet::OnRep_MaxManaPoints(const FGameplayAttributeData& OldMaxManaPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxManaPoints, OldMaxManaPoints);
}

// + StaminaPoints Attribute Replication
void UAuraAttributeSet::OnRep_StaminaPoints(const FGameplayAttributeData& OldStaminaPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, StaminaPoints, OldStaminaPoints);
}

// + MaxStaminaPoints Attribute Replication
void UAuraAttributeSet::OnRep_MaxStaminaPoints(const FGameplayAttributeData& OldMaxStaminaPoints) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxStaminaPoints, OldMaxStaminaPoints);
}


// End Replications

// Section Pre-Changes

/**
 * Notify function called before an attribute is changed.
 *
 * @param Attribute The attribute being changed.
 * @param NewValue The new value of the attribute.
 */
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHitPointsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHitPoints());
	}
	if (Attribute == GetManaPointsAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxManaPoints());
	}
}

// End Pre-Changes

// Section Post Changes

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	PopulateEffectProperties(Data);

	if (Data.EvaluatedData.Attribute == GetHitPointsAttribute())
	{
		SetHitPoints(FMath::Clamp(GetHitPoints(), 0, GetMaxHitPoints()));
	}
}

//? Store Post Effect Execute Data
void UAuraAttributeSet::PopulateEffectProperties(const FGameplayEffectModCallbackData& Data)
{
	SetEffectContextHandle(Data);
	SetEffectProperty(EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent(), SourceEffectProperty);
	SetEffectProperty(&Data.Target, TargetEffectProperty);
}

// End Post Changes


// Section Helper Methods

//~ Set Effect Properties
void UAuraAttributeSet::SetEffectProperty(UAbilitySystemComponent* AbilitySystemComponent, FEffectProperty& EffectProperty)
{
	if (AbilitySystemComponent->AbilityActorInfo.IsValid() && AbilitySystemComponent->GetAvatarActor())
	{
		EffectProperty.AbilitySystemComponent = AbilitySystemComponent;
		EffectProperty.AvtarActor = AbilitySystemComponent->GetAvatarActor();
		EffectProperty.Controller = GetController(AbilitySystemComponent);
		EffectProperty.Character = GetCharacter(EffectProperty.Controller);
	}
}

//~ GetAbility System
UAbilitySystemComponent* UAuraAttributeSet::GetAbilitySystemComponent(const FGameplayEffectContextHandle& EffectContextHandle)
{
	return EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
}

//~ Get Character
ACharacter* UAuraAttributeSet::GetCharacter(const UAbilitySystemComponent* AbilitySystemComponent)
{
	if (const AController* Controller = GetController(AbilitySystemComponent))
	{
		return GetCharacter(Controller);
	}
	return nullptr;
}

ACharacter* UAuraAttributeSet::GetCharacter(const AController* Controller)
{
	return Cast<ACharacter>(Controller->GetPawn());
}

//~ Get Controller
AController* UAuraAttributeSet::GetController(const UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AController* TempController = AbilitySystemComponent->AbilityActorInfo->PlayerController.Get())
		return TempController;
	
	const AActor* AvatarActor = AbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
	return GetController(AvatarActor);
}

//~ Get Controller Overload
AController* UAuraAttributeSet::GetController(const AActor* Actor)
{
	if (const APawn* Pawn = Cast<APawn>(Actor))
	{
		return Pawn->GetController();
	}
	return nullptr;
}
