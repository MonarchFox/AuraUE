// Coded By MonarchFox


#include "Actor/AreaOfEffect/AuraAOEBase.h"
#include "NiagaraComponent.h"
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

	// + Binding Collision Properties
	InitOverlapDelegation();
}

void AAuraAOEBase::InitOverlapDelegation()
{
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraAOEBase::OnComponentOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAuraAOEBase::OnComponentOverlapEnd);
}

void AAuraAOEBase::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GameplayEffectOnOverlap(OtherActor);
}

void AAuraAOEBase::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GameplayEffectOnEndOverlap(OtherActor);
}
