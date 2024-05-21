// Coded By @niffo.dev


#include "Actor/Projectile/AuraProjectileCast.h"
#include "Components/SphereComponent.h"


AAuraProjectileCast::AAuraProjectileCast()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	//~ SphereComponent Construction
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);

	// + Setting Up SphereComponent Overlap Config
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
}

void AAuraProjectileCast::BeginPlay()
{
	Super::BeginPlay();
}
