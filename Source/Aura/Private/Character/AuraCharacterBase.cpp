// Coded By MonarchFox

#include "Character/AuraCharacterBase.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Region StaticMeshComponents Constructor

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponComponent");
	WeaponComponent->SetupAttachment(GetMesh(), WeaponComponentSocketName);
	WeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// End Region
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
