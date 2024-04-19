// Coded By MonarchFox

#include "Character/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Section StaticMeshComponents Constructor

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponComponent");
	WeaponComponent->SetupAttachment(GetMesh(), WeaponComponentSocketName);
	WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// End
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
