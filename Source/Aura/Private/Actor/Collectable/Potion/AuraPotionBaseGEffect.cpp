// Coded By MonarchFox


#include "Actor/Collectable/Potion/AuraPotionBaseGEffect.h"
#include "Character/AuraCharacter.h"
#include "Components/SphereComponent.h"


AAuraPotionBaseGEffect::AAuraPotionBaseGEffect()
{
	// !Defaults
	PrimaryActorTick.bCanEverTick = false;

	//+ PotionBody Mesh Component
	PotionBody = CreateDefaultSubobject<UStaticMeshComponent>("PotionBody");
	SetRootComponent(PotionBody);
	PotionBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//+ PotionCollision Component
	PotionCollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	PotionCollisionComponent->SetupAttachment(GetRootComponent());
}

void AAuraPotionBaseGEffect::BeginPlay()
{
	Super::BeginPlay();
	PotionCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraPotionBaseGEffect::OnSphereOverlapBegin);
}

void AAuraPotionBaseGEffect::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAuraCharacter* PlayerCharacter = Cast<AAuraCharacter>(OtherActor))
	{
		ApplyEffectToTarget(OtherActor, PotionEffect);
		Destroy();
	}
}
