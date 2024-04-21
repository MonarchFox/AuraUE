// Coded By MonarchFox


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


AAuraPlayerState::AAuraPlayerState()
{
	// !Defaults

	// + Client & Server Defaults
	NetUpdateFrequency = GetClientUpdateFrequency();

	// + Ability System Defaults
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(IsReplicationRequired());
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
}
