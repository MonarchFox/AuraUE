// Coded By MonarchFox

#include "Actor/Projectile/AuraProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "Interaction/CombatInterface.h"


AAuraProjectileBase::AAuraProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	//~ SphereComponent Construction
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComponent);

	// + Setting Up SphereComponent Overlap Config
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionObjectType(ECC_Projectile);
	SphereComponent->SetCollisionResponseToChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);

	// +  ProjectileMovement Component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = PROJECTILE_INITIAL_SPEED;
	ProjectileMovementComponent->MaxSpeed = PROJECTILE_MAX_SPEED;
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
	SetLifeSpan(5.f);
	PlaySoundEffect(BodySound, true);
}

void AAuraProjectileBase::Destroyed()
{
	ShutDownProjectileSounds();
	if (!bHit && !HasAuthority())
	{
		SpawnNiagaraEffect(ImpactEffect);
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
	if (!CanCollide(OtherActor)) return;
	
	ShutDownProjectileSounds();
	SpawnNiagaraEffect(ImpactEffect);
	PlaySoundEffect(ImpactSound);

	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetAbilitySystemComponent
			= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

// Section Initials End

// Section Helper Functions

bool AAuraProjectileBase::CanCollide(AActor* Actor) const
{
	checkf(OwnerActor, TEXT("Configure Who is Firing the projectile in PorjectileSpell"));

	if (const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Actor))
	{
		return CombatInterface != OwnerActor;
	}
	
	return true;
}

void AAuraProjectileBase::SetOwnerActor(const ICombatInterface* Actor)
{
	if (Actor) OwnerActor = Actor;
}

void AAuraProjectileBase::PlaySoundEffect(USoundBase* SFX, bool bAttach)
{

	if (!SFX)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Sound Effect Passed To Play At AuraProjectileBase Class"));
		return;
	}

	if (!bAttach)
	{
		UGameplayStatics::PlaySoundAtLocation
		(
			this,
			SFX,
			GetActorLocation(),
			FRotator::ZeroRotator
		);
	}else
	{
		ProjectileSound = UGameplayStatics::SpawnSoundAttached(
			SFX, GetRootComponent()
		);
	}
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
