// Coded By MonarchFox


#include "Actor/AreaOfEffect/AuraAOEBase.h"
#include "NiagaraComponent.h"
#include "Character/AuraCharacter.h"
#include "Components/SphereComponent.h"


AAuraAOEBase::AAuraAOEBase()
{
	// !Defaults

	// + Root Component
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("BoxComponent");
	SphereComponent->SetupAttachment(GetRootComponent());

	// + Niagara Component
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComponent->SetupAttachment(GetRootComponent());
}

void AAuraAOEBase::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraAOEBase::OnComponentOverlapBegin);
}

void AAuraAOEBase::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAuraCharacter* PlayerCharacter = Cast<AAuraCharacter>(OtherActor))
	{
		ApplyEffectToTarget(OtherActor, GetAOEGameplayEffect());
	}
}
