// Coded By MonarchFox

#include "Actor/Projectile/AuraProjectileBase.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


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

	// +  ProjectileMovement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 2000;
	ProjectileMovementComponent->MaxSpeed = 3000;
	ProjectileMovementComponent->ProjectileGravityScale = PROJECTILE_GRAVITY_SCALE;

	// + Body Niagara Component
	BodyEffect = CreateDefaultSubobject<UNiagaraComponent>("BodyNiagaraComponent");
	BodyEffect->SetupAttachment(GetRootComponent());
}

void AAuraProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//~ Initials
	InitSphereStructureComponent();
}

void AAuraProjectileBase::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		// SpawnNiagaraEffect(ImpactEffect);
		PlaySoundEffect(ImpactSound);
	}
	Super::Destroyed();
}

// Section Initials

void AAuraProjectileBase::InitSphereStructureComponent()
{
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectileBase::OnBeginOverlapSphereComponent);
}

void AAuraProjectileBase::OnBeginOverlapSphereComponent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnNiagaraEffect(ImpactEffect);
	PlaySoundEffect(ImpactSound);

	if (HasAuthority()) Destroy();
	else bHit = true;
}

// Section Initials End

// Section Helper Functions

void AAuraProjectileBase::PlaySoundEffect(USoundBase* SFX) const
{

	if (!SFX)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Sound Effect Passed To Play At AuraProjectileBase Class"));
		return;
	}
	
	UGameplayStatics::PlaySoundAtLocation
	(
		this,
		SFX,
		GetActorLocation(),
		FRotator::ZeroRotator
	);
}

void AAuraProjectileBase::SpawnNiagaraEffect(UNiagaraSystem* VFX) const
{
	if (!VFX)
	{
		UE_LOG(LogTemp, Error, TEXT("Null VFX Effect Passed To Play At AuraProjectileBase Class"));
		return;
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation
	(
		this,
		VFX,
		GetActorLocation()
	);
}

// End Helper Functions
