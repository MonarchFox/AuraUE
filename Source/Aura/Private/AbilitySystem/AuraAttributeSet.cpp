// Coded By MonarchFox


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	// !Defaults

	//? For Debug Purpose Only
	InitHitPoints(50.f);
	InitMaxHitPoints(120.f);

	InitMaxManaPoints(200.f);
	InitManaPoints(150.f);
}

// Section Replications

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

// + All Attribute Replication Properties Setup
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
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// !Replication Properties Setup
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// + Health Attribute Setup
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HitPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHitPoints, COND_None, REPNOTIFY_Always);

	// + Mana Attribute Setup
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaPoints, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxManaPoints, COND_None, REPNOTIFY_Always);
}

// End Replications
