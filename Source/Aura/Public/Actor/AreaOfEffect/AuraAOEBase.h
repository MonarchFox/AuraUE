// Coded By MonarchFox

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraEffectActor.h"
#include "AuraAOEBase.generated.h"


class USphereComponent;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class AURA_API AAuraAOEBase : public AAuraEffectActor
{
	GENERATED_BODY()

	//? Meta Information
	UPROPERTY(EditAnywhere, Category="Custom", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	//? Meta Function (Replace On Inheritance)
	UFUNCTION()
	void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AAuraAOEBase();

	//! Must Override On Inheritance
	virtual void InitOverlapDelegation();
	
protected:
	virtual void BeginPlay() override;

	//~ Body Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
};
