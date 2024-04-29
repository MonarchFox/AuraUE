// Coded By MonarchFox

#include "Character/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Section StaticMeshComponents Constructor

	WeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>("WeaponComponent");
	WeaponComponent->SetupAttachment(GetMesh(), WeaponComponentSocketName);
	WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// End
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

/**~		Initial Attribute Setup			*/
void AAuraCharacterBase::InitialPrimaryAttribute() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GetDefaultPrimaryAttribute());
	
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();

	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()
	->MakeOutgoingSpec(GetDefaultPrimaryAttribute(), 1.f, ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),
		GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
	
}
