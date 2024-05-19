// Coded By MonarchFox

#include "Actor/Projectile/AuraProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AAuraProjectileBase::AAuraProjectileBase()
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

	//~ ProjectileMovement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 0;
	ProjectileMovementComponent->MaxSpeed = 0;
	ProjectileMovementComponent->ProjectileGravityScale = PROJECTILE_GRAVITY_SCALE;
}

void AAuraProjectileBase::ProjectileLaunched()
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector(VelocitySpeed, 0, 0));
}

void AAuraProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//~ Initials
	InitSphereStructureComponent();
}

// Section Initials

void AAuraProjectileBase::InitSphereStructureComponent()
{
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectileBase::OnBeginOverlapSphereComponent);
}

void AAuraProjectileBase::OnBeginOverlapSphereComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


// Section Initials End
