// Coded By MonarchFox

#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Section StaticMeshComponents Constructor

	WeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>("WeaponComponent");
	WeaponComponent->SetupAttachment(GetMesh(), WeaponComponentSocketName);
	WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// End
}

// Section Interface Implementation

FVector AAuraCharacterBase::GetCombatSocketLocation() const
{
	if (!WeaponComponent->DoesSocketExist(WeaponTipSocketName)) return FVector();
	return WeaponComponent->GetSocketLocation(WeaponTipSocketName);
}

// End Interface Implementation

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
	
}

/**~		Initial Default Attribute Setup			*/
void AAuraCharacterBase::InitGameplayEffectToSelf(const TSubclassOf<UGameplayEffect> AttributeEffect, const float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(AttributeEffect);
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()
	->MakeOutgoingSpec(AttributeEffect, Level, ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),
		GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitialDefaultAttributes() const
{
	InitGameplayEffectToSelf(GetDefaultPrimaryAttribute(), 1.0);
	InitGameplayEffectToSelf(GetDefaultSecondaryAttribute(), 1.0);
}

void AAuraCharacterBase::AddCharacterAbility()
{
	if (!HasAuthority()) return;

	UAuraAbilitySystemComponent* AbilitySystemComponent = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent());
	AbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}
