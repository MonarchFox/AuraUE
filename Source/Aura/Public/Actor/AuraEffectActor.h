// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"


class USphereComponent;


UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	// Sections Inits (things which should be needed at begin play time)
	void InitOverlappingComponent();
	
	UFUNCTION()
	virtual void OnOverlapBeginActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEndActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// End Inits

protected:
	virtual void BeginPlay() override;

private:
	
	// Section Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	// End Components

public:

};
