// Coded By MonarchFox

#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	// !Defaults
	PrimaryActorTick.bCanEverTick = false;

	// + Mesh Component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(MeshComponent);
	
	// + Sphere Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());
	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// !Initials
	InitOverlappingComponent();
}

// Sections Inits (things which should be needed at begin play time)

// + SphereComponent Overlap
void AAuraEffectActor::InitOverlappingComponent()
{
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlapBeginActor);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlapEndActor);
}

void AAuraEffectActor::OnOverlapBeginActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASIPlayer = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASIPlayer->GetAbilitySystemComponent()
		->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		//? Debug Purpose Only
		UAuraAttributeSet* TempAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		TempAuraAttributeSet->SetHitPoints(AuraAttributeSet->GetHitPoints() + 100.f);

		Destroy();
	}
}

void AAuraEffectActor::OnOverlapEndActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

// End Inits
